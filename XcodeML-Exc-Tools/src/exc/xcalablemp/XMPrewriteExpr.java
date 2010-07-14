package exc.xcalablemp;

import exc.block.*;
import exc.object.*;

public class XMPrewriteExpr {
  private XMPglobalDecl		_globalDecl;
  private XMPobjectTable	_globalObjectTable;

  public XMPrewriteExpr(XMPglobalDecl globalDecl) {
    _globalDecl = globalDecl;
    _globalObjectTable = globalDecl.getGlobalObjectTable();
  }

  public void rewrite(FuncDefBlock def) throws XMPexception {
    FunctionBlock fb = def.getBlock();
    if (fb == null) return;

    // rewrite expr
    XMPobjectTable localObjectTable = XMPlocalDecl.getObjectTable(fb);

    BasicBlockExprIterator iter = new BasicBlockExprIterator(fb);
    for (iter.init(); !iter.end(); iter.next())
      rewriteExpr(iter.getExpr(), localObjectTable);

    // create local object descriptors, constructors and desctructors
    XMPlocalDecl.setupObjectId(fb);
    XMPlocalDecl.setupConstructor(fb);
    XMPlocalDecl.setupDestructor(fb);

    def.Finalize();
  }

  public void rewriteExpr(Xobject expr, XMPobjectTable localObjectTable) throws XMPexception {
    if (expr == null) return;

    bottomupXobjectIterator iter = new bottomupXobjectIterator(expr);
    iter.init();
    while (!iter.end()) {
      Xobject newExpr = null;
      Xobject myExpr = iter.getXobject();
      if (myExpr == null) {
        iter.next();
        continue;
      }

      switch (myExpr.Opcode()) {
        case ARRAY_REF:
          {
            String arrayName = myExpr.getSym();
            XMPalignedArray alignedArray = _globalObjectTable.getAlignedArray(arrayName);
            if (alignedArray == null)
              alignedArray = localObjectTable.getAlignedArray(arrayName);

            if (alignedArray != null) {
              if (alignedArray.checkRealloc()) {
                iter.next();
                rewriteAlignedArrayExpr(iter, alignedArray);
                break;
              }
            }

            iter.next();
            break;
          }
        default:
          iter.next();
      }
    }
  }

  private void rewriteAlignedArrayExpr(bottomupXobjectIterator iter,
                                       XMPalignedArray alignedArray) throws XMPexception {
    XobjList getAddrFuncArgs = Xcons.List(alignedArray.getAddrId().Ref());
    parseArrayExpr(iter, alignedArray, 0, getAddrFuncArgs);
  }

  private void parseArrayExpr(bottomupXobjectIterator iter,
                              XMPalignedArray alignedArray, int arrayDimCount, XobjList args) throws XMPexception {
    String syntaxErrMsg = "syntax error on array expression, cannot rewrite distributed array";
    Xobject prevExpr = iter.getPrevXobject();
    Xobject myExpr = iter.getXobject();
    LineNo lnObj = myExpr.getLineNo();
    Xobject parentExpr = iter.getParent();
    switch (myExpr.Opcode()) {
      case PLUS_EXPR:
        {
          switch (prevExpr.Opcode()) {
            case ARRAY_REF:
              {
                if (arrayDimCount != 0)
                  XMP.error(lnObj, syntaxErrMsg);

                break;
              }
            case POINTER_REF:
              break;
            default:
              {
                XMP.error(lnObj, syntaxErrMsg);
                break;
              }
          }

          if (parentExpr.Opcode() == Xcode.POINTER_REF) {
            args.add(getCalcIndexFuncRef(alignedArray, arrayDimCount, myExpr.right()));
            iter.next();
            parseArrayExpr(iter, alignedArray, arrayDimCount + 1, args);
          }
          else {
            Xobject funcCall = createRewriteAlignedArrayFunc(alignedArray, arrayDimCount, args);
            myExpr.setLeft(funcCall);
            iter.next();
          }

          return;
        }
      case POINTER_REF:
        {
          switch (prevExpr.Opcode()) {
            case PLUS_EXPR:
              break;
            default:
              {
                XMP.error(lnObj, syntaxErrMsg);
                break;
              }
          }

          iter.next();
          parseArrayExpr(iter, alignedArray, arrayDimCount, args);
          return;
        }
      default:
        {
          Xobject funcCall = createRewriteAlignedArrayFunc(alignedArray, arrayDimCount, args);
          iter.setPrevXobject(funcCall);
          return;
        }
    }
  }

  private Xobject createRewriteAlignedArrayFunc(XMPalignedArray alignedArray, int arrayDimCount, XobjList getAddrFuncArgs) {
    int arrayDim = alignedArray.getDim();
    Ident getAddrFuncId = null;
    if (arrayDimCount == arrayDim) {
      getAddrFuncId = XMP.getMacroId("_XCALABLEMP_M_GET_ELMT_" + arrayDim);
      for (int i = 0; i < arrayDim - 1; i++)
        getAddrFuncArgs.add(alignedArray.getGtolAccIdAt(i).Ref());
    }
    else {
      getAddrFuncId = XMP.getMacroId("_XCALABLEMP_M_GET_ADDR_" + arrayDimCount);
      for (int i = 0; i < arrayDimCount; i++)
        getAddrFuncArgs.add(alignedArray.getGtolAccIdAt(i).Ref());
    }

    return getAddrFuncId.Call(getAddrFuncArgs);
  }

  private Xobject getCalcIndexFuncRef(XMPalignedArray alignedArray, int index, Xobject indexRef) throws XMPexception {
    int distManner = alignedArray.getDistMannerAt(index);
    switch (distManner) {
      case XMPalignedArray.NO_ALIGN:
      case XMPtemplate.DUPLICATION:
        return indexRef;
      case XMPtemplate.BLOCK:
        if (alignedArray.hasShadow()) {
          XMPshadow shadow = alignedArray.getShadowAt(index);
          switch (shadow.getType()) {
            case XMPshadow.SHADOW_NONE:
              {
                XobjList args = Xcons.List(indexRef,
                                           alignedArray.getGtolTemp0IdAt(index).Ref());
                return XMP.getMacroId("_XCALABLEMP_M_CALC_INDEX_BLOCK").Call(args);
              }
            case XMPshadow.SHADOW_FULL:
              return indexRef;
            case XMPshadow.SHADOW_NORMAL:
              {
                XobjList args = Xcons.List(indexRef,
                                           alignedArray.getGtolTemp0IdAt(index).Ref(),
                                           shadow.getLo());
                return XMP.getMacroId("_XCALABLEMP_M_CALC_INDEX_BLOCK_W_SHADOW").Call(args);
              }
            default:
              XMP.error(alignedArray.getLineNo(), "unknown shadow type");
          }
        }
        else {
          XobjList args = Xcons.List(indexRef,
                                     alignedArray.getGtolTemp0IdAt(index).Ref());
          return XMP.getMacroId("_XCALABLEMP_M_CALC_INDEX_BLOCK").Call(args);
        }
      case XMPtemplate.CYCLIC:
        if (alignedArray.hasShadow()) {
          XMPshadow shadow = alignedArray.getShadowAt(index);
          switch (shadow.getType()) {
            case XMPshadow.SHADOW_NONE:
              {
                XobjList args = Xcons.List(indexRef,
                                           alignedArray.getGtolTemp0IdAt(index).Ref());
                return XMP.getMacroId("_XCALABLEMP_M_CALC_INDEX_CYCLIC").Call(args);
              }
            case XMPshadow.SHADOW_FULL:
              return indexRef;
            case XMPshadow.SHADOW_NORMAL:
              XMP.error(alignedArray.getLineNo(), "only block distribution allows shadow");
            default:
              XMP.error(alignedArray.getLineNo(), "unknown shadow type");
          }
        }
        else {
          XobjList args = Xcons.List(indexRef,
                                     alignedArray.getGtolTemp0IdAt(index).Ref());
          return XMP.getMacroId("_XCALABLEMP_M_CALC_INDEX_CYCLIC").Call(args);
        }
      default:
        XMP.error(alignedArray.getLineNo(), "unknown distribute manner for array '" + alignedArray.getName()  + "'");
    }

    // XXX not reach here
    return null;
  }
}

/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
package xcodeml.c.decompile;

public interface XcSourcePositioned
{
    /**
     * Gets the source code position object of the object.
      *
     * @return the source code position object.
      */
     public XcSourcePosObj getSourcePos();
     
     /**
      * Sets the source code position object to the object.
       *
      * @param srcPos the source code position object.
       */
     public void setSourcePos(XcSourcePosObj srcPos);
}

/*
 * The Relaxer artifact
 * Copyright (c) 2000-2003, ASAMI Tomoharu, All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer. 
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
package xcodeml.c.binding.gen;

import xcodeml.binding.*;

import java.io.*;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.Writer;
import java.net.URL;
import javax.xml.parsers.*;
import org.w3c.dom.*;
import org.xml.sax.*;

/**
 * <b>XbcFunctionDecl</b> is generated from XcodeML_C.rng by Relaxer.
 * This class is derived from:
 * 
 * <!-- for programmer
 * <element java:extends="xcodeml.c.obj.XmcObj" java:implements="xcodeml.c.binding.IXbcStatement" name="functionDecl">
 *   <ref name="BaseStatement"/>
 *   <ref name="name"/>
 *   <optional>
 *     <ref name="gccAsm"/>
 *   </optional>
 * </element>
 * -->
 * <!-- for javadoc -->
 * <pre> &lt;element java:extends="xcodeml.c.obj.XmcObj" java:implements="xcodeml.c.binding.IXbcStatement" name="functionDecl"&gt;
 *   &lt;ref name="BaseStatement"/&gt;
 *   &lt;ref name="name"/&gt;
 *   &lt;optional&gt;
 *     &lt;ref name="gccAsm"/&gt;
 *   &lt;/optional&gt;
 * &lt;/element&gt;
 * </pre>
 *
 * @version XcodeML_C.rng (Thu Feb 02 16:55:19 JST 2012)
 * @author  Relaxer 1.0 (http://www.relaxer.org)
 */
public class XbcFunctionDecl extends xcodeml.c.obj.XmcObj implements java.io.Serializable, Cloneable, xcodeml.c.binding.IXbcStatement, IRVisitable, IRNode, IXbcDeclarationsChoice, IXbcGlobalDeclarationsChoice {
    public static final String ISGCCSYNTAX_0 = "0";
    public static final String ISGCCSYNTAX_1 = "1";
    public static final String ISGCCSYNTAX_TRUE = "true";
    public static final String ISGCCSYNTAX_FALSE = "false";
    public static final String ISMODIFIED_0 = "0";
    public static final String ISMODIFIED_1 = "1";
    public static final String ISMODIFIED_TRUE = "true";
    public static final String ISMODIFIED_FALSE = "false";

    private String lineno_;
    private String rawlineno_;
    private String file_;
    private String isGccSyntax_;
    private String isModified_;
    private XbcName name_;
    private XbcGccAsm gccAsm_;
    private IRNode parentRNode_;

    /**
     * Creates a <code>XbcFunctionDecl</code>.
     *
     */
    public XbcFunctionDecl() {
    }

    /**
     * Creates a <code>XbcFunctionDecl</code>.
     *
     * @param source
     */
    public XbcFunctionDecl(XbcFunctionDecl source) {
        setup(source);
    }

    /**
     * Creates a <code>XbcFunctionDecl</code> by the Stack <code>stack</code>
     * that contains Elements.
     * This constructor is supposed to be used internally
     * by the Relaxer system.
     *
     * @param stack
     */
    public XbcFunctionDecl(RStack stack) {
        setup(stack);
    }

    /**
     * Creates a <code>XbcFunctionDecl</code> by the Document <code>doc</code>.
     *
     * @param doc
     */
    public XbcFunctionDecl(Document doc) {
        setup(doc.getDocumentElement());
    }

    /**
     * Creates a <code>XbcFunctionDecl</code> by the Element <code>element</code>.
     *
     * @param element
     */
    public XbcFunctionDecl(Element element) {
        setup(element);
    }

    /**
     * Creates a <code>XbcFunctionDecl</code> by the File <code>file</code>.
     *
     * @param file
     * @exception IOException
     * @exception SAXException
     * @exception ParserConfigurationException
     */
    public XbcFunctionDecl(File file) throws IOException, SAXException, ParserConfigurationException {
        setup(file);
    }

    /**
     * Creates a <code>XbcFunctionDecl</code>
     * by the String representation of URI <code>uri</code>.
     *
     * @param uri
     * @exception IOException
     * @exception SAXException
     * @exception ParserConfigurationException
     */
    public XbcFunctionDecl(String uri) throws IOException, SAXException, ParserConfigurationException {
        setup(uri);
    }

    /**
     * Creates a <code>XbcFunctionDecl</code> by the URL <code>url</code>.
     *
     * @param url
     * @exception IOException
     * @exception SAXException
     * @exception ParserConfigurationException
     */
    public XbcFunctionDecl(URL url) throws IOException, SAXException, ParserConfigurationException {
        setup(url);
    }

    /**
     * Creates a <code>XbcFunctionDecl</code> by the InputStream <code>in</code>.
     *
     * @param in
     * @exception IOException
     * @exception SAXException
     * @exception ParserConfigurationException
     */
    public XbcFunctionDecl(InputStream in) throws IOException, SAXException, ParserConfigurationException {
        setup(in);
    }

    /**
     * Creates a <code>XbcFunctionDecl</code> by the InputSource <code>is</code>.
     *
     * @param is
     * @exception IOException
     * @exception SAXException
     * @exception ParserConfigurationException
     */
    public XbcFunctionDecl(InputSource is) throws IOException, SAXException, ParserConfigurationException {
        setup(is);
    }

    /**
     * Creates a <code>XbcFunctionDecl</code> by the Reader <code>reader</code>.
     *
     * @param reader
     * @exception IOException
     * @exception SAXException
     * @exception ParserConfigurationException
     */
    public XbcFunctionDecl(Reader reader) throws IOException, SAXException, ParserConfigurationException {
        setup(reader);
    }

    /**
     * Initializes the <code>XbcFunctionDecl</code> by the XbcFunctionDecl <code>source</code>.
     *
     * @param source
     */
    public void setup(XbcFunctionDecl source) {
        int size;
        setLineno(source.getLineno());
        setRawlineno(source.getRawlineno());
        setFile(source.getFile());
        setIsGccSyntax(source.getIsGccSyntax());
        setIsModified(source.getIsModified());
        if (source.name_ != null) {
            setName((XbcName)source.getName().clone());
        }
        if (source.gccAsm_ != null) {
            setGccAsm((XbcGccAsm)source.getGccAsm().clone());
        }
    }

    /**
     * Initializes the <code>XbcFunctionDecl</code> by the Document <code>doc</code>.
     *
     * @param doc
     */
    public void setup(Document doc) {
        setup(doc.getDocumentElement());
    }

    /**
     * Initializes the <code>XbcFunctionDecl</code> by the Element <code>element</code>.
     *
     * @param element
     */
    public void setup(Element element) {
        init(element);
    }

    /**
     * Initializes the <code>XbcFunctionDecl</code> by the Stack <code>stack</code>
     * that contains Elements.
     * This constructor is supposed to be used internally
     * by the Relaxer system.
     *
     * @param stack
     */
    public void setup(RStack stack) {
        init(stack.popElement());
    }

    /**
     * @param element
     */
    private void init(Element element) {
        IXcodeML_CFactory factory = XcodeML_CFactory.getFactory();
        RStack stack = new RStack(element);
        lineno_ = URelaxer.getAttributePropertyAsString(element, "lineno");
        rawlineno_ = URelaxer.getAttributePropertyAsString(element, "rawlineno");
        file_ = URelaxer.getAttributePropertyAsString(element, "file");
        isGccSyntax_ = URelaxer.getAttributePropertyAsString(element, "is_gccSyntax");
        isModified_ = URelaxer.getAttributePropertyAsString(element, "is_modified");
        setName(factory.createXbcName(stack));
        if (XbcGccAsm.isMatch(stack)) {
            setGccAsm(factory.createXbcGccAsm(stack));
        }
    }

    /**
     * @return Object
     */
    public Object clone() {
        IXcodeML_CFactory factory = XcodeML_CFactory.getFactory();
        return (factory.createXbcFunctionDecl(this));
    }

    /**
     * Creates a DOM representation of the object.
     * Result is appended to the Node <code>parent</code>.
     *
     * @param parent
     */
    public void makeElement(Node parent) {
        Document doc;
        if (parent instanceof Document) {
            doc = (Document)parent;
        } else {
            doc = parent.getOwnerDocument();
        }
        Element element = doc.createElement("functionDecl");
        int size;
        if (this.lineno_ != null) {
            URelaxer.setAttributePropertyByString(element, "lineno", this.lineno_);
        }
        if (this.rawlineno_ != null) {
            URelaxer.setAttributePropertyByString(element, "rawlineno", this.rawlineno_);
        }
        if (this.file_ != null) {
            URelaxer.setAttributePropertyByString(element, "file", this.file_);
        }
        if (this.isGccSyntax_ != null) {
            URelaxer.setAttributePropertyByString(element, "is_gccSyntax", this.isGccSyntax_);
        }
        if (this.isModified_ != null) {
            URelaxer.setAttributePropertyByString(element, "is_modified", this.isModified_);
        }
        this.name_.makeElement(element);
        if (this.gccAsm_ != null) {
            this.gccAsm_.makeElement(element);
        }
        parent.appendChild(element);
    }

    /**
     * Initializes the <code>XbcFunctionDecl</code> by the File <code>file</code>.
     *
     * @param file
     * @exception IOException
     * @exception SAXException
     * @exception ParserConfigurationException
     */
    public void setup(File file) throws IOException, SAXException, ParserConfigurationException {
        setup(file.toURL());
    }

    /**
     * Initializes the <code>XbcFunctionDecl</code>
     * by the String representation of URI <code>uri</code>.
     *
     * @param uri
     * @exception IOException
     * @exception SAXException
     * @exception ParserConfigurationException
     */
    public void setup(String uri) throws IOException, SAXException, ParserConfigurationException {
        setup(UJAXP.getDocument(uri, UJAXP.FLAG_NONE));
    }

    /**
     * Initializes the <code>XbcFunctionDecl</code> by the URL <code>url</code>.
     *
     * @param url
     * @exception IOException
     * @exception SAXException
     * @exception ParserConfigurationException
     */
    public void setup(URL url) throws IOException, SAXException, ParserConfigurationException {
        setup(UJAXP.getDocument(url, UJAXP.FLAG_NONE));
    }

    /**
     * Initializes the <code>XbcFunctionDecl</code> by the InputStream <code>in</code>.
     *
     * @param in
     * @exception IOException
     * @exception SAXException
     * @exception ParserConfigurationException
     */
    public void setup(InputStream in) throws IOException, SAXException, ParserConfigurationException {
        setup(UJAXP.getDocument(in, UJAXP.FLAG_NONE));
    }

    /**
     * Initializes the <code>XbcFunctionDecl</code> by the InputSource <code>is</code>.
     *
     * @param is
     * @exception IOException
     * @exception SAXException
     * @exception ParserConfigurationException
     */
    public void setup(InputSource is) throws IOException, SAXException, ParserConfigurationException {
        setup(UJAXP.getDocument(is, UJAXP.FLAG_NONE));
    }

    /**
     * Initializes the <code>XbcFunctionDecl</code> by the Reader <code>reader</code>.
     *
     * @param reader
     * @exception IOException
     * @exception SAXException
     * @exception ParserConfigurationException
     */
    public void setup(Reader reader) throws IOException, SAXException, ParserConfigurationException {
        setup(UJAXP.getDocument(reader, UJAXP.FLAG_NONE));
    }

    /**
     * Creates a DOM document representation of the object.
     *
     * @exception ParserConfigurationException
     * @return Document
     */
    public Document makeDocument() throws ParserConfigurationException {
        Document doc = UJAXP.makeDocument();
        makeElement(doc);
        return (doc);
    }

    /**
     * Gets the String property <b>lineno</b>.
     *
     * @return String
     */
    public final String getLineno() {
        return (lineno_);
    }

    /**
     * Sets the String property <b>lineno</b>.
     *
     * @param lineno
     */
    public final void setLineno(String lineno) {
        this.lineno_ = lineno;
    }

    /**
     * Gets the String property <b>rawlineno</b>.
     *
     * @return String
     */
    public final String getRawlineno() {
        return (rawlineno_);
    }

    /**
     * Sets the String property <b>rawlineno</b>.
     *
     * @param rawlineno
     */
    public final void setRawlineno(String rawlineno) {
        this.rawlineno_ = rawlineno;
    }

    /**
     * Gets the String property <b>file</b>.
     *
     * @return String
     */
    public final String getFile() {
        return (file_);
    }

    /**
     * Sets the String property <b>file</b>.
     *
     * @param file
     */
    public final void setFile(String file) {
        this.file_ = file;
    }

    /**
     * Gets the String property <b>isGccSyntax</b>.
     *
     * @return String
     */
    public final String getIsGccSyntax() {
        return (isGccSyntax_);
    }

    /**
     * Sets the String property <b>isGccSyntax</b>.
     *
     * @param isGccSyntax
     */
    public final void setIsGccSyntax(String isGccSyntax) {
        this.isGccSyntax_ = isGccSyntax;
    }

    /**
     * Gets the String property <b>isModified</b>.
     *
     * @return String
     */
    public final String getIsModified() {
        return (isModified_);
    }

    /**
     * Sets the String property <b>isModified</b>.
     *
     * @param isModified
     */
    public final void setIsModified(String isModified) {
        this.isModified_ = isModified;
    }

    /**
     * Gets the XbcName property <b>name</b>.
     *
     * @return XbcName
     */
    public final XbcName getName() {
        return (name_);
    }

    /**
     * Sets the XbcName property <b>name</b>.
     *
     * @param name
     */
    public final void setName(XbcName name) {
        this.name_ = name;
        if (name != null) {
            name.rSetParentRNode(this);
        }
    }

    /**
     * Gets the XbcGccAsm property <b>gccAsm</b>.
     *
     * @return XbcGccAsm
     */
    public final XbcGccAsm getGccAsm() {
        return (gccAsm_);
    }

    /**
     * Sets the XbcGccAsm property <b>gccAsm</b>.
     *
     * @param gccAsm
     */
    public final void setGccAsm(XbcGccAsm gccAsm) {
        this.gccAsm_ = gccAsm;
        if (gccAsm != null) {
            gccAsm.rSetParentRNode(this);
        }
    }

    /**
     * Makes an XML text representation.
     *
     * @return String
     */
    public String makeTextDocument() {
        StringBuffer buffer = new StringBuffer();
        makeTextElement(buffer);
        return (new String(buffer));
    }

    /**
     * Makes an XML text representation.
     *
     * @param buffer
     */
    public void makeTextElement(StringBuffer buffer) {
        int size;
        buffer.append("<functionDecl");
        if (lineno_ != null) {
            buffer.append(" lineno=\"");
            buffer.append(URelaxer.escapeAttrQuot(URelaxer.getString(getLineno())));
            buffer.append("\"");
        }
        if (rawlineno_ != null) {
            buffer.append(" rawlineno=\"");
            buffer.append(URelaxer.escapeAttrQuot(URelaxer.getString(getRawlineno())));
            buffer.append("\"");
        }
        if (file_ != null) {
            buffer.append(" file=\"");
            buffer.append(URelaxer.escapeAttrQuot(URelaxer.getString(getFile())));
            buffer.append("\"");
        }
        if (isGccSyntax_ != null) {
            buffer.append(" is_gccSyntax=\"");
            buffer.append(URelaxer.escapeAttrQuot(URelaxer.getString(getIsGccSyntax())));
            buffer.append("\"");
        }
        if (isModified_ != null) {
            buffer.append(" is_modified=\"");
            buffer.append(URelaxer.escapeAttrQuot(URelaxer.getString(getIsModified())));
            buffer.append("\"");
        }
        buffer.append(">");
        name_.makeTextElement(buffer);
        if (gccAsm_ != null) {
            gccAsm_.makeTextElement(buffer);
        }
        buffer.append("</functionDecl>");
    }

    /**
     * Makes an XML text representation.
     *
     * @param buffer
     * @exception IOException
     */
    public void makeTextElement(Writer buffer) throws IOException {
        int size;
        buffer.write("<functionDecl");
        if (lineno_ != null) {
            buffer.write(" lineno=\"");
            buffer.write(URelaxer.escapeAttrQuot(URelaxer.getString(getLineno())));
            buffer.write("\"");
        }
        if (rawlineno_ != null) {
            buffer.write(" rawlineno=\"");
            buffer.write(URelaxer.escapeAttrQuot(URelaxer.getString(getRawlineno())));
            buffer.write("\"");
        }
        if (file_ != null) {
            buffer.write(" file=\"");
            buffer.write(URelaxer.escapeAttrQuot(URelaxer.getString(getFile())));
            buffer.write("\"");
        }
        if (isGccSyntax_ != null) {
            buffer.write(" is_gccSyntax=\"");
            buffer.write(URelaxer.escapeAttrQuot(URelaxer.getString(getIsGccSyntax())));
            buffer.write("\"");
        }
        if (isModified_ != null) {
            buffer.write(" is_modified=\"");
            buffer.write(URelaxer.escapeAttrQuot(URelaxer.getString(getIsModified())));
            buffer.write("\"");
        }
        buffer.write(">");
        name_.makeTextElement(buffer);
        if (gccAsm_ != null) {
            gccAsm_.makeTextElement(buffer);
        }
        buffer.write("</functionDecl>");
    }

    /**
     * Makes an XML text representation.
     *
     * @param buffer
     */
    public void makeTextElement(PrintWriter buffer) {
        int size;
        buffer.print("<functionDecl");
        if (lineno_ != null) {
            buffer.print(" lineno=\"");
            buffer.print(URelaxer.escapeAttrQuot(URelaxer.getString(getLineno())));
            buffer.print("\"");
        }
        if (rawlineno_ != null) {
            buffer.print(" rawlineno=\"");
            buffer.print(URelaxer.escapeAttrQuot(URelaxer.getString(getRawlineno())));
            buffer.print("\"");
        }
        if (file_ != null) {
            buffer.print(" file=\"");
            buffer.print(URelaxer.escapeAttrQuot(URelaxer.getString(getFile())));
            buffer.print("\"");
        }
        if (isGccSyntax_ != null) {
            buffer.print(" is_gccSyntax=\"");
            buffer.print(URelaxer.escapeAttrQuot(URelaxer.getString(getIsGccSyntax())));
            buffer.print("\"");
        }
        if (isModified_ != null) {
            buffer.print(" is_modified=\"");
            buffer.print(URelaxer.escapeAttrQuot(URelaxer.getString(getIsModified())));
            buffer.print("\"");
        }
        buffer.print(">");
        name_.makeTextElement(buffer);
        if (gccAsm_ != null) {
            gccAsm_.makeTextElement(buffer);
        }
        buffer.print("</functionDecl>");
    }

    /**
     * Makes an XML text representation.
     *
     * @param buffer
     */
    public void makeTextAttribute(StringBuffer buffer) {
    }

    /**
     * Makes an XML text representation.
     *
     * @param buffer
     * @exception IOException
     */
    public void makeTextAttribute(Writer buffer) throws IOException {
    }

    /**
     * Makes an XML text representation.
     *
     * @param buffer
     */
    public void makeTextAttribute(PrintWriter buffer) {
    }

    /**
     * Gets the property value as String.
     *
     * @return String
     */
    public String getLinenoAsString() {
        return (URelaxer.getString(getLineno()));
    }

    /**
     * Gets the property value as String.
     *
     * @return String
     */
    public String getRawlinenoAsString() {
        return (URelaxer.getString(getRawlineno()));
    }

    /**
     * Gets the property value as String.
     *
     * @return String
     */
    public String getFileAsString() {
        return (URelaxer.getString(getFile()));
    }

    /**
     * Gets the property value as String.
     *
     * @return String
     */
    public String getIsGccSyntaxAsString() {
        return (URelaxer.getString(getIsGccSyntax()));
    }

    /**
     * Gets the property value as String.
     *
     * @return String
     */
    public String getIsModifiedAsString() {
        return (URelaxer.getString(getIsModified()));
    }

    /**
     * Sets the property value by String.
     *
     * @param string
     */
    public void setLinenoByString(String string) {
        setLineno(string);
    }

    /**
     * Sets the property value by String.
     *
     * @param string
     */
    public void setRawlinenoByString(String string) {
        setRawlineno(string);
    }

    /**
     * Sets the property value by String.
     *
     * @param string
     */
    public void setFileByString(String string) {
        setFile(string);
    }

    /**
     * Sets the property value by String.
     *
     * @param string
     */
    public void setIsGccSyntaxByString(String string) {
        setIsGccSyntax(string);
    }

    /**
     * Sets the property value by String.
     *
     * @param string
     */
    public void setIsModifiedByString(String string) {
        setIsModified(string);
    }

    /**
     * Returns a String representation of this object.
     * While this method informs as XML format representaion, 
     *  it's purpose is just information, not making 
     * a rigid XML documentation.
     *
     * @return String
     */
    public String toString() {
        try {
            return (makeTextDocument());
        } catch (Exception e) {
            return (super.toString());
        }
    }

    /**
     * Accepts the Visitor for enter behavior.
     *
     * @param visitor
     * @return boolean
     */
    public boolean enter(IRVisitor visitor) {
        return (visitor.enter(this));
    }

    /**
     * Accepts the Visitor for leave behavior.
     *
     * @param visitor
     */
    public void leave(IRVisitor visitor) {
        visitor.leave(this);
    }

    /**
     * Gets the IRNode property <b>parentRNode</b>.
     *
     * @return IRNode
     */
    public final IRNode rGetParentRNode() {
        return (parentRNode_);
    }

    /**
     * Sets the IRNode property <b>parentRNode</b>.
     *
     * @param parentRNode
     */
    public final void rSetParentRNode(IRNode parentRNode) {
        this.parentRNode_ = parentRNode;
    }

    /**
     * Gets child RNodes.
     *
     * @return IRNode[]
     */
    public IRNode[] rGetRNodes() {
        java.util.List classNodes = new java.util.ArrayList();
        if (name_ != null) {
            classNodes.add(name_);
        }
        if (gccAsm_ != null) {
            classNodes.add(gccAsm_);
        }
        IRNode[] nodes = new IRNode[classNodes.size()];
        return ((IRNode[])classNodes.toArray(nodes));
    }

    /**
     * Tests if a Element <code>element</code> is valid
     * for the <code>XbcFunctionDecl</code>.
     *
     * @param element
     * @return boolean
     */
    public static boolean isMatch(Element element) {
        if (!URelaxer.isTargetElement(element, "functionDecl")) {
            return (false);
        }
        RStack target = new RStack(element);
        boolean $match$ = false;
        Element child;
        if (!XbcName.isMatchHungry(target)) {
            return (false);
        }
        $match$ = true;
        if (XbcGccAsm.isMatchHungry(target)) {
        }
        if (!target.isEmptyElement()) {
            return (false);
        }
        return (true);
    }

    /**
     * Tests if elements contained in a Stack <code>stack</code>
     * is valid for the <code>XbcFunctionDecl</code>.
     * This mehtod is supposed to be used internally
     * by the Relaxer system.
     *
     * @param stack
     * @return boolean
     */
    public static boolean isMatch(RStack stack) {
        Element element = stack.peekElement();
        if (element == null) {
            return (false);
        }
        return (isMatch(element));
    }

    /**
     * Tests if elements contained in a Stack <code>stack</code>
     * is valid for the <code>XbcFunctionDecl</code>.
     * This method consumes the stack contents during matching operation.
     * This mehtod is supposed to be used internally
     * by the Relaxer system.
     *
     * @param stack
     * @return boolean
     */
    public static boolean isMatchHungry(RStack stack) {
        Element element = stack.peekElement();
        if (element == null) {
            return (false);
        }
        if (isMatch(element)) {
            stack.popElement();
            return (true);
        } else {
            return (false);
        }
    }
}
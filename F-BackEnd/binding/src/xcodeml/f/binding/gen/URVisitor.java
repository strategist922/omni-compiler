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
package xcodeml.f.binding.gen;

import xcodeml.binding.*;

/**
 * URVisitor
 *
 * @since   Apr. 30, 2000
 * @version Dec. 17, 2003
 * @author  ASAMI, Tomoharu (asami@relaxer.org)
 */
public final class URVisitor {
    public static void traverse(IRNode node, IRVisitor visitor) {
        traverseDepth(node, visitor);
    }

    public static void traverseDepth(IRNode node, IRVisitor visitor) {
        IRVisitable visitable = (IRVisitable)node;
        if (visitable.enter(visitor)) {
            traverseDepthChildren(node, visitor);
            visitable.leave(visitor);
        }
    }

    public static void traverseDepthChildren(
        IRNode node,
        IRVisitor visitor
    ) {
        traverseDepthChildren(node.rGetRNodes(), visitor);
    }

    public static void traverseDepthChildren(
        IRNode[] children,
        IRVisitor visitor
    ) {
        for (int i = 0;i < children.length;i++) {
            traverseDepth(children[i], visitor);
        }
    }

    public static void traverseBreadth(IRNode node, IRVisitor visitor) {
        IRVisitable visitable = (IRVisitable)node;
        if (visitable.enter(visitor)) {
            traverseBreadthChildren(node, visitor);
        }
        visitable.leave(visitor);
    }

    public static void traverseBreadthChildren(
        IRNode node,
        IRVisitor visitor
    ) {
        IRNode[] children = node.rGetRNodes();
        boolean[] enterResult = new boolean[children.length];
        for (int i = 0;i < children.length;i++) {
            IRVisitable visitable = (IRVisitable)children[i];
            enterResult[i] = visitable.enter(visitor);
            visitable.leave(visitor);
        }
        for (int i = 0;i < children.length;i++) {
            IRNode child = children[i];
            if (enterResult[i]) {
                traverseBreadthChildren(child, visitor);
            }
        }
    }
}
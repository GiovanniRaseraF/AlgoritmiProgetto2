package Algorithms;

public class RedBlackTreeNode extends Node {

    public static final RedBlackTreeNode NIL = new RedBlackTreeNode();

    private byte color;

    public final static byte RED    = 0x0;
    public final static byte BLACK  = 0x1;

    public RedBlackTreeNode() {
        super();
        this.color = BLACK;
    }

    public RedBlackTreeNode(int key, String value) {
        super(key, value);
        this.left 	= RedBlackTreeNode.NIL;
        this.right 	= RedBlackTreeNode.NIL;
        this.parent	= RedBlackTreeNode.NIL;
        this.color = RED;
    }

    public RedBlackTreeNode getLeft() {
        return ((RedBlackTreeNode) super.getLeft());
    }

    public RedBlackTreeNode getRight() {
        return ((RedBlackTreeNode) super.getRight());
    }

    public RedBlackTreeNode getParent() {
        return ((RedBlackTreeNode) super.getParent());
    }

    public byte getColor() {
        return color;
    }

    public void setColor(byte color) {
        this.color = color;
    }
}

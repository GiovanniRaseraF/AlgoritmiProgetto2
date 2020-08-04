package Algorithms;

public class AvlNode extends Node {
    public static final AvlNode NIL = new AvlNode();

    private int height;

    public AvlNode() {
        super();
        this.height = 0;
    }

    public AvlNode(int key, String value, int height) {
        super(key, value);
        this.parent = AvlNode.NIL;
        this.left = AvlNode.NIL;
        this.right = AvlNode.NIL;
        this.height = height;
        this.getLeft().setParent(this);
        this.getRight().setParent(this);
    }

    public static AvlNode getNIL() {
        return NIL;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public AvlNode getLeft() {
        return ((AvlNode) super.getLeft());
    }

    public AvlNode getRight() {
        return ((AvlNode) super.getRight());
    }

    public AvlNode getParent() {
        return ((AvlNode) super.getParent());
    }
}
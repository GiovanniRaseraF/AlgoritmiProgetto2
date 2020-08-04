package Algorithms;

public class Node {

    protected Node parent, left, right;
    private String value;
    private boolean nil;
    private final int key;

    public static final Node NIL = new Node();

    public Node() {
        this.key = Integer.MIN_VALUE;
        this.nil = true;
    }

    public Node(int key, String value) {
        this.value = value;
        this.left = new Node();
        this.right = new Node();
        this.key = key;
    }

    public Node getParent() {
        return parent;
    }

    public void setParent(Node parent) {
        this.parent = parent;
    }

    public Node getLeft() {
        return left;
    }

    public void setLeft(Node left) {
        this.left = left;
    }

    public Node getRight() {
        return right;
    }

    public void setRight(Node right) {
        this.right = right;
    }

    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
    }

    public boolean isNil() {
        return nil;
    }

    public void setNil(boolean nil) {
        this.nil = nil;
    }

    public int getKey() {
        return key;
    }

    public boolean equals(Node node) {
        return (nil && node.nil) || (key == node.key);
    }

}

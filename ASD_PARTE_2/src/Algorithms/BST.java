package Algorithms;

public class BST extends Tree implements Trees {
    public BST() {
        super();
    }


    @Override
    public boolean insert(int key, String value) {
        Node x = root;
        Node y = Node.NIL;
        Node z = new Node(key, value);

        while (!x.equals(Node.NIL)) {
            y = x;
            if (x.getKey() > z.getKey()) {
                x = x.getLeft();
            } else {
                x = x.getRight();
            }
        }
        if (y.equals(Node.NIL)) {
            root = z;
        } else {
            z.setParent(y);
            if (y.getKey() > z.getKey())
                y.setLeft(z);
            else
                y.setRight(z);
        }
        return true;
    }

    @Override
    public Node search(int key) {
        Node x = root;

        while (!x.equals(Node.NIL)) {
            if (x.getKey() == key) {
                return x;
            } else if (x.getKey() > key) {
                x = x.getLeft();
            } else {
                x = x.getRight();
            }
        }
        return Node.NIL;
    }

    @Override
    public void reset() {
        this.root = Node.NIL;
    }
}

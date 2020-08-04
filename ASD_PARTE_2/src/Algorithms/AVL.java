package Algorithms;

public class AVL extends Tree implements Trees {
    public AVL() {
        root = (AvlNode) AvlNode.NIL;
    }

    // Return number of unbalanced nodes on subtrees
    private int unBalancedNodes(AvlNode avl) {
        if (!avl.equals(AvlNode.NIL)) {
            return getHeight(avl.getLeft()) - getHeight(avl.getRight());
        }
        return 0;
    }


    private int getHeight(AvlNode avl) {
        if (avl == null || avl.equals(AvlNode.NIL)) {
            return 0;
        }
        return avl.getHeight();
    }


    private AvlNode rotateRight(AvlNode avlR) {
        AvlNode avlL = avlR.getLeft();
        AvlNode b = avlL.getRight();

        avlL.setRight(avlR);
        avlR.setLeft(b);
        avlR.setHeight(Math.max(getHeight(avlR.getLeft()), getHeight(avlR.getRight())) + 1);
        avlL.setHeight(Math.max(getHeight(avlL.getLeft()), getHeight(avlL.getRight())) + 1);

        return avlL;
    }


    private AvlNode rotateLeft(AvlNode avlL) {
        AvlNode avlR = avlL.getRight();
        AvlNode b = avlR.getLeft();

        avlR.setLeft(avlL);
        avlL.setRight(b);

        avlL.setHeight(Math.max(getHeight(avlL.getLeft()), getHeight(avlL.getRight())) + 1);
        avlR.setHeight(Math.max(getHeight(avlR.getLeft()), getHeight(avlR.getRight())) + 1);

        return avlR;
    }


    private Node insert(AvlNode avl, int key, String value) {

        if (avl.equals(AvlNode.NIL)) {
            return (new AvlNode(key, value, 1));
        }
        if (key < avl.getKey()) {
            avl.setLeft(insert(avl.getLeft(), key, value));
        } else {
            avl.setRight(insert(avl.getRight(), key, value));
        }

        // Update the height
        avl.setHeight(1 + Math.max(getHeight(avl.getLeft()), getHeight(avl.getRight())));
        int balance = unBalancedNodes(avl);

        if (balance > 1 && key < avl.getLeft().getKey()) {
            return rotateRight(avl);
        }

        if (balance < -1 && key > avl.getRight().getKey()) {
            return rotateLeft(avl);
        }

        if (balance > 1 && key > avl.getLeft().getKey()) {
            avl.setLeft(rotateLeft(avl.getLeft()));
            return rotateRight(avl);
        }

        if (balance < -1 && key < avl.getRight().getKey()) {
            avl.setRight(rotateRight(avl.getRight()));
            return rotateLeft(avl);
        }

        return avl;
    }


    @Override
    public boolean insert(int key, String value) {
        this.root = insert((AvlNode) this.root, key, value);
        return true;
    }


    @Override
    public AvlNode search(int key) {
        AvlNode x = (AvlNode) root;

        while (!x.equals(AvlNode.NIL)) {
            if (x.getKey() == key) {
                return x;
            } else if (x.getKey() > key) {
                x = x.getLeft();
            } else {
                x = x.getRight();
            }
        }

        return AvlNode.NIL;
    }

    @Override
    public void reset() {
        this.root = (AvlNode) AvlNode.NIL;
    }
}

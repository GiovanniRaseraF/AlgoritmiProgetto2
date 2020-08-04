package Algorithms;

public class RBT extends Tree implements Trees {
    public RBT() {
        super();
        root = RedBlackTreeNode.NIL;
    }


    private void rotateRight(RedBlackTreeNode red) {
        RedBlackTreeNode left = red.getLeft();
        red.setLeft(left.getRight());
        if (!left.getRight().equals(RedBlackTreeNode.NIL)) {
            left.getRight().setParent(red);
        }
        left.setParent(red.getParent());
        if (red.parent.equals(RedBlackTreeNode.NIL)) {
            this.root = left;
        } else if (red.equals(red.getParent().getRight())) {
            red.getParent().setRight(left);
        } else {
            red.getParent().setLeft(left);
        }
        left.setRight(red);
        red.setParent(left);
    }

    private void rotateLeft(RedBlackTreeNode red) {
        RedBlackTreeNode rigth = red.getRight();
        red.setRight(rigth.getLeft());
        if (!rigth.getLeft().equals(RedBlackTreeNode.NIL)) {
            rigth.getLeft().setParent(red);
        }
        rigth.setParent(red.getParent());
        if (red.parent.equals(RedBlackTreeNode.NIL)) {
            this.root = rigth;
        } else if (red.equals(red.getParent().getLeft())) {
            red.getParent().setLeft(rigth);
        } else {
            red.getParent().setRight(rigth);
        }
        rigth.setLeft(red);
        red.setParent(rigth);
    }


    @Override
    public boolean insert(int key, String value) {
        insert(new RedBlackTreeNode(key, value));
        return true;
    }

    private void insert(RedBlackTreeNode z) {

        RedBlackTreeNode y = RedBlackTreeNode.NIL;
        RedBlackTreeNode x = (RedBlackTreeNode) root;
        while (!x.equals(RedBlackTreeNode.NIL)) {
            y = x;
            if (z.getKey() < x.getKey()) {
                x = x.getLeft();
            } else {
                x = x.getRight();
            }
        }
        z.setParent(y);
        if (y.equals(RedBlackTreeNode.NIL)) {
            root = z;
        } else if (z.getKey() < y.getKey()) {
            y.setLeft(z);
        } else {
            y.setRight(z);
        }
        if (z.getParent().equals(RedBlackTreeNode.NIL)) {
            z.setColor(RedBlackTreeNode.BLACK);
            return;
        }
        if (z.getParent().getParent().equals(RedBlackTreeNode.NIL)) {
            return;
        }
        FixInsert(z);

    }

    private void FixInsert(RedBlackTreeNode z) {
        RedBlackTreeNode uncle;
        while (z.getParent().getColor() == RedBlackTreeNode.RED) {
            if (z.getParent().equals(z.getParent().getParent().getRight())) {
                uncle = z.getParent().getParent().getLeft();

                if (uncle.getColor() == RedBlackTreeNode.RED) {
                    uncle.setColor(RedBlackTreeNode.BLACK);
                    z.getParent().setColor(RedBlackTreeNode.BLACK);
                    z.getParent().getParent().setColor(RedBlackTreeNode.RED);
                    z = z.getParent().getParent();
                } else {
                    if (z.equals(z.getParent().left)) {
                        z = z.getParent();
                        rotateRight(z);
                    }
                    z.getParent().setColor(RedBlackTreeNode.BLACK);
                    z.getParent().getParent().setColor(RedBlackTreeNode.RED);
                    rotateLeft(z.getParent().getParent());
                }
            } else {
                uncle = z.getParent().getParent().getRight();
                if (uncle.getColor() == RedBlackTreeNode.RED) {
                    uncle.setColor(RedBlackTreeNode.BLACK);
                    z.getParent().setColor(RedBlackTreeNode.BLACK);
                    z.getParent().getParent().setColor(RedBlackTreeNode.RED);
                    z = z.getParent().getParent();

                } else {
                    if (z.equals(z.getParent().getRight())) {
                        z = z.getParent();
                        rotateLeft(z);
                    }
                    z.getParent().setColor(RedBlackTreeNode.BLACK);
                    z.getParent().getParent().setColor(RedBlackTreeNode.RED);
                    rotateRight(z.getParent().getParent());
                }

            }
            if (z.equals(root)) {
                break;
            }
        }
        ((RedBlackTreeNode) root).setColor(RedBlackTreeNode.BLACK);
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
        this.root = RedBlackTreeNode.NIL;
    }
}

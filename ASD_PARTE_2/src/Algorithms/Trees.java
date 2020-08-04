package Algorithms;

public interface Trees {
    // Trees interface with methods in common for all trees
    boolean insert(int key, String value);
    Node search(int key);
    void reset();
}

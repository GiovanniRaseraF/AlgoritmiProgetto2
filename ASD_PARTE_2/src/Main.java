import Algorithms.*;

import java.util.ArrayList;
import java.util.Arrays;

public class Main {
    public static void main(String[] args) {

        // Variables names are self explicative
        int numberOfTotalSamples = 100;
        int initialRepetition = 1000;
        int maxRepetitions = 1000000;
        int iterationsForPrecision = 50;
        double minError = 0.01;

        // Needed to keep track of the number of repetitions (and arraySize)
        int repetitionsCounter;

        // Trees declaration
        BST bst = new BST();
        AVL avl = new AVL();
        RBT rbt = new RBT();
        ArrayList<Trees> trees = new ArrayList<>();
        trees.add(bst);
        trees.add(avl);
        trees.add(rbt);

        // Repeat 100 times
        for (int i = 0; i < numberOfTotalSamples; i++) {
            double base = Math.exp((Math.log(maxRepetitions) - Math.log(initialRepetition)) / (numberOfTotalSamples - 1));
            repetitionsCounter = (int) ((double) initialRepetition * Math.pow(base, i));
            System.out.print(repetitionsCounter + " ");

            // Repeat for all the 3 algorithms
            for (int tree = 0; tree < trees.size(); tree++) {
                double deviation = 0d;
                double currentTotalTime = 0d;
                ArrayList<Double> tempMemory = new ArrayList<>();
                // Repeat iterationsForPrecision times to increase the precision
                for (int k = 0; k < iterationsForPrecision; k++) {
                    trees.get(tree).reset();
                    // Get the time each time finish repetitionsCounter
                    double currentTime = insertOperation(trees.get(tree), repetitionsCounter, minError);
                    currentTotalTime += currentTime;
                    tempMemory.add(currentTime);
                    System.gc();
                }
                // Ammortised Time
                double ammortisedTime = currentTotalTime / iterationsForPrecision;
                System.out.print(ammortisedTime + " ");

                // Variance
                for (Double time : tempMemory) {
                    deviation += Math.pow(time - ammortisedTime, 2);
                }
                deviation = (Math.sqrt(deviation / iterationsForPrecision));
                System.out.print(deviation + " ");

            }

            System.out.println();

        }

    }


    private static double getMachineBasedTimeResolution() {
        long startT, endT;
        long[] value = new long[10000];

        for (int i = 0; i < 10000; i++) {
            startT = System.nanoTime();
            do {
                endT = System.nanoTime();
            } while (startT == endT);
            value[i] = endT - startT;
        }
        Arrays.sort(value);
        return value[value.length / 2];
    }


    private static double getTime(Params p, double risoluzione, double errMin) {

        long timeS, timeE;
        int c = 0, c1;
        timeS = System.nanoTime();
        do {
            c1 = p.selected();
            timeE = System.nanoTime();
            c++;
        } while (timeE - timeS <= risoluzione * (1.0 / errMin) + 1.0);
        return ((timeE - timeS) / c) / c1;
    }

    private static double insertOperation(Trees tree, int randomArraySize, double minErr) {
        double MinResolution = getMachineBasedTimeResolution();
        RandomArray randomArray = new RandomArray();
        int k[] = randomArray.newArray(randomArraySize);

        Params p = new Params() {
            public int k[];

            public void setK(int[] k) {
                this.k = k;
            }

            @Override
            public int selected() {
                int c = 0;
                for (int i = 0; i < k.length; i++) {
                    if (tree.search(k[i]).equals(Node.NIL)) {
                        tree.insert(k[i], "test" + i);
                        c++;
                    }
                }
                return c;
            }

        };
        p.setK(k);
        return getTime(p, MinResolution, minErr);
    }
}


interface Params {
    int selected();

    void setK(int[] k);
}
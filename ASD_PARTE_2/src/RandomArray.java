import org.apache.commons.math3.random.MersenneTwister;

public class RandomArray {

    public int[] newArray(int dimensione) {

        int min = -dimensione / 2;
        int max = dimensione / 2;

        MersenneTwister random = new MersenneTwister();
        int[] array = new int[dimensione];

        for (int i = 0; i < dimensione; i++) {
            array[i] = (int) ((random.nextInt(max - min + 1)) + min);
        }
        return array;
    }

}
import java.util.ArrayList;
import java.util.List;
import java.lang.Thread;
import java.lang.ref.WeakReference;

public class RuntimeMemoryTest {
    public static void main(String[] args) {
        Runtime runtime = Runtime.getRuntime();
        List<WeakReference<int[]>> listOfArrays = new ArrayList<>();
        int i = 0;

        System.out.println("Initial memory state:");
        printMemoryStats(runtime);

        while (true){
            for (i = 0; i < 1000; i++) {
                int[] array = new int[100000]; // 100k integers
                listOfArrays.add(new WeakReference<>(array));
            }

            System.out.println("\nAfter adding " + (i + 1) + " arrays:");
            printMemoryStats(runtime);
        }
    }

    private static void printMemoryStats(Runtime runtime) {
        long totalMemory = runtime.totalMemory();
        long freeMemory = runtime.freeMemory();
        long usedMemory = totalMemory - freeMemory;

        System.out.println(java.lang.String.format("Total Memory: %s MB", bytesToMB(totalMemory)));
        System.out.println(java.lang.String.format("Free Memory: %s MB", bytesToMB(freeMemory)));
        System.out.println(java.lang.String.format("Used Memory: %s MB", bytesToMB(usedMemory)));
        System.out.println(java.lang.String.format("Max Memory: %s MB", bytesToMB(runtime.maxMemory())));
    }

    private static double bytesToMB(long bytes) {
        return bytes / (1024.0 * 1024.0);
    }
}

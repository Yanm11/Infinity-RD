public class Ex2NoSync {
    private static long counter = 0;

    public static void main(String[] args) throws InterruptedException {
        Thread t1 = new Thread(() -> {
            for (int i = 0; i < 10_000_000; i++) {
                counter++;
            }
        });

        Thread t2 = new Thread(() -> {
            for (int i = 0; i < 10_000_000; i++) {
                counter++;
            }
        });

        long startTime = System.currentTimeMillis();

        t1.start();
        t2.start();

        t1.join();
        t2.join();

        long endTime = System.currentTimeMillis();

        System.out.println("Counter: " + counter);
        System.out.println("Time taken (no synchronization): " + (endTime - startTime) + " ms");
    }
}

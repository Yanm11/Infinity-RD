public class Ex2SyncBlock {

    private static long counter = 0;
    private static final Object lock = new Object();

    public static void main(String[] args) throws InterruptedException {
        Thread t1 = new Thread(() -> {
            for (int i = 0; i < 10_000_000; i++) {
                synchronized (lock) {
                    counter++;
                }
            }
        });

        Thread t2 = new Thread(() -> {
            for (int i = 0; i < 10_000_000; i++) {
                synchronized (lock) {
                    counter++;
                }
            }
        });

        long startTime = System.currentTimeMillis();

        t1.start();
        t2.start();

        t1.join();
        t2.join();

        long endTime = System.currentTimeMillis();

        System.out.println("Counter: " + counter);
        System.out.println("Time taken (synchronized block): " + (endTime - startTime) + " ms");
    }
}



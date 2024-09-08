public class Ex2SyncMethod {

    private static long counter = 0;

    public static synchronized void increment() {
        counter++;
    }

    public static void main(String[] args) throws InterruptedException {
        Thread t1 = new Thread(() -> {
            for (int i = 0; i < 10_000_000; i++) {
                increment();
            }
        });

        Thread t2 = new Thread(() -> {
            for (int i = 0; i < 10_000_000; i++) {
                increment();
            }
        });

        long startTime = System.currentTimeMillis();

        t1.start();
        t2.start();

        t1.join();
        t2.join();

        long endTime = System.currentTimeMillis();

        System.out.println("Counter: " + counter);
        System.out.println("Time taken (synchronized method): " + (endTime - startTime) + " ms");
    }
}



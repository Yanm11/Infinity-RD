import java.util.concurrent.atomic.AtomicLong;


public class Ex2AtomicSync {
    private static AtomicLong counter = new AtomicLong(0);

    public static void main(String[] args) throws InterruptedException {
        Thread t1 = new Thread(() -> {
            for (int i = 0; i < 10_000_000; i++) {
                counter.incrementAndGet();
            }
        });

        Thread t2 = new Thread(() -> {
            for (int i = 0; i < 10_000_000; i++) {
                counter.incrementAndGet();
            }
        });

        long startTime = System.currentTimeMillis();

        t1.start();
        t2.start();

        t1.join();
        t2.join();

        long endTime = System.currentTimeMillis();

        System.out.println("Counter: " + counter);
        System.out.println("Time taken (atomic): " + (endTime - startTime) + " ms");
    }
}



import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;



public class Ex2reentrentLock {
    private static long counter = 0;
    private static Lock lock = new ReentrantLock();

    public static void main(String[] args) throws InterruptedException {
        Thread t1 = new Thread(() -> {
            for (int i = 0; i < 10_000_000; i++) {
                lock.lock();
                try {
                    counter++;
                } finally {
                    lock.unlock();
                }
            }
        });

        Thread t2 = new Thread(() -> {
            for (int i = 0; i < 10_000_000; i++) {
                lock.lock();
                try {
                    counter++;
                } finally {
                    lock.unlock();
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
        System.out.println("Time taken (reentrant lock): " + (endTime - startTime) + " ms");
    }
}



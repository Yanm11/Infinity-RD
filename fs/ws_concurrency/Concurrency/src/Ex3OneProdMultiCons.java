import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.Condition;

public class Ex3OneProdMultiCons {
    private static int data = 0;
    private static final int NUM_OF_THREADS = 5;
    private static Semaphore readDataSem = new Semaphore(0);
    private static final Lock lock = new ReentrantLock();
    private static final Condition consumed  = lock.newCondition();
    private static volatile int countConsumed = 0;

    public static void main(String[] args) {
        Thread producer = new Thread() {
            @Override
            public void run() {
                while (true) {
                    lock.lock();
                        // produce the data
                        ++data;

                        //raise the semaphore to number of threads and counter for consumed meseeges
                        readDataSem.release(NUM_OF_THREADS);
                        countConsumed = NUM_OF_THREADS;

                        //wake all the threads up
                        consumed.signalAll();

                        //go to sleep
                        while (countConsumed != 0) {
                            try {
                                consumed.await();
                            }
                            catch (InterruptedException ignored) {}
                        }
                    lock.unlock();
                }
            }
        };

        producer.start();

        for (int i = 0; i < NUM_OF_THREADS; ++i) {
            Thread consumer = new Thread() {
                @Override
                public void run() {
                    while (true) {
                        //getting the confermation that the messege was created
                        try {
                            readDataSem.acquire();
                        }
                        catch (InterruptedException ignored) {}

                        lock.lock();

                        // print the data
                        System.out.println(data + " " + Thread.currentThread().getName());
                        --countConsumed;

                        if (countConsumed == 0) {
                            consumed.signalAll();
                        }

                        //wait until a new message is ready
                        try {
                            consumed.await();
                        } catch (InterruptedException ignored) {
                        }

                        lock.unlock();

                        //slow down the printing
                        try{
                            sleep(2000);
                        }
                        catch (InterruptedException ignored) {}
                    }
                }
            };

            consumer.start();
        }
    }
}

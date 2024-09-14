import java.util.LinkedList;
import java.util.concurrent.Semaphore;

import static java.lang.Thread.sleep;

public class Ex3MltiProdMultiConsSyncSem {
    private static final Object lock = new Object();
    private static LinkedList<Integer> list = new LinkedList<>();
    private static Semaphore isemptySem = new Semaphore(0);

    public static void main(String[] args) {
        //creating consumer threads
        for (int i = 0; i < 5; ++i) {
           Thread consumer =  new Thread() {
                @Override
                public void run() {
                    while (true) {
                        try {
                            isemptySem.acquire();
                        } catch (InterruptedException ignored) {
                        }

                        synchronized (lock) {
                            System.out.println("got: " + list.poll());
                        }
                    }
                }
            };

           consumer.start();
        }

        try {
            sleep(5000);
        } catch (InterruptedException ignored) {
        }


        //creating producer threads
        for (int i = 0; i < 5; ++i) {
            Thread producer =  new Thread() {
                @Override
                public void run() {
                    while (true) {
                        synchronized (lock) {
                            Integer randomNumber = (int) (Math.random() * 101);
                            list.add(randomNumber);
                            isemptySem.release();
                        }
                        try {
                            sleep(2000);
                        } catch (InterruptedException ignored) {
                        }
                    }
                }
            };

            producer.start();
        }
    }
}

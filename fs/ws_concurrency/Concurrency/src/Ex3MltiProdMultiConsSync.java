import java.util.LinkedList;
import java.util.LinkedList;

import static java.lang.Thread.sleep;

public class Ex3MltiProdMultiConsSync {
    private static final Object lock = new Object();
    private static LinkedList<Integer> list = new LinkedList<>();

    public static void main(String[] args) {
        //creating consumer threads
        for (int i = 0; i < 5; ++i) {
           Thread consumer =  new Thread() {
                @Override
                public void run() {
                    while (true) {
                        if (!list.isEmpty()) {
                            synchronized (lock) {
                                if (!list.isEmpty()) {
                                    System.out.println("got: " + list.poll());
                                }
                            }
                        }
                        else {
                            try {
                                sleep(500);
                            } catch (InterruptedException ignored) {
                            }
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

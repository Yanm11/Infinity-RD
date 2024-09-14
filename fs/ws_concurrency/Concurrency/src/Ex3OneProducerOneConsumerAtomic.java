import java.util.LinkedList;
import java.util.concurrent.atomic.AtomicInteger;

public class Ex3OneProducerOneConsumerAtomic {
    private static AtomicInteger lock = new AtomicInteger(0);

    public static void main(String[] args) {

        Thread producer = new Thread() {
            @Override
            public void run() {
                while (true) {
                    if (lock.get() == 0) {

                        System.out.println("Ping!");
                        //realising the lock
                        lock.incrementAndGet();
                        try {
                            sleep(1000);
                        } catch (InterruptedException ignored) {
                        }
                    }
                }
            }
        };


        Thread consumer = new Thread() {
            @Override
            public void run() {
                while (true) {
                    if (lock.get() == 1) {

                        System.out.println("Pong!");
                        //realising the lock
                        lock.decrementAndGet();
                        try {
                            sleep(2000);
                        } catch (InterruptedException ignored) {
                        }
                    }
                }
            }
        };

        producer.start();
        consumer.start();
    }
}

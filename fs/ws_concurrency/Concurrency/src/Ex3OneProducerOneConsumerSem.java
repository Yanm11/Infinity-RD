import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

public class Ex3OneProducerOneConsumerSem {
    private static Semaphore semUploadData = new Semaphore(0);
    private static Semaphore semReadData = new Semaphore(1);
    private static AtomicInteger counter = new AtomicInteger(0);

    public static void main(String[] args) {
        Thread producer = new Thread() {
            @Override
            public void run() {
                while (true) {
                    try {
                        semReadData.acquire();
                    } catch (InterruptedException ignored) {
                    }

                    System.out.println("Ping!");
                    semUploadData.release();
                    try {
                        sleep(1000);
                    }
                    catch (InterruptedException ignored) {}
                }
            }
        };

        Thread consumer = new Thread() {
            @Override
            public void run() {
                while (true) {
                    try {
                        semUploadData.acquire();
                    } catch (InterruptedException ignored) {
                    }

                    System.out.println("Pong!");
                    semReadData.release();
                    try {
                        sleep(1000);
                    }
                    catch (InterruptedException ignored) {}
                }
            }
        };

        producer.start();
        consumer.start();
    }
}

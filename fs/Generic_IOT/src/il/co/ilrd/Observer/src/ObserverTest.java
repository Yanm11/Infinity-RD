package il.co.ilrd.Observer.src;

import static org.junit.Assert.*;
import org.junit.Test;
import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.function.Consumer;

public class ObserverTest {

    @Test
    public void testSingleSubscriberReceivesData() {
        Publisher<String> publisher = new Publisher<>();

        AtomicReference<String> receivedData = new AtomicReference<>();
        Consumer<String> consumer = data -> receivedData.set(data);
        Runnable stopUpdateRunnable = () -> {};

        Subscriber<String> subscriber = new Subscriber<>(consumer, stopUpdateRunnable);
        subscriber.register(publisher);

        String testData = "Hello, Observer!";
        publisher.produce(testData);

        assertEquals(testData, subscriber.getData());
        assertEquals(testData, receivedData.get());
    }

    @Test
    public void testMultipleSubscribersReceiveData() {
        Publisher<Integer> publisher = new Publisher<>();

        AtomicReference<Integer> receivedData1 = new AtomicReference<>();
        Consumer<Integer> consumer1 = data -> receivedData1.set(data);
        Runnable stopUpdateRunnable1 = () -> {};
        Subscriber<Integer> subscriber1 = new Subscriber<>(consumer1, stopUpdateRunnable1);
        subscriber1.register(publisher);

        AtomicReference<Integer> receivedData2 = new AtomicReference<>();
        Consumer<Integer> consumer2 = data -> receivedData2.set(data);
        Runnable stopUpdateRunnable2 = () -> {};
        Subscriber<Integer> subscriber2 = new Subscriber<>(consumer2, stopUpdateRunnable2);
        subscriber2.register(publisher);

        Integer testData = 42;
        publisher.produce(testData);

        assertEquals(testData, subscriber1.getData());
        assertEquals(testData, receivedData1.get());

        assertEquals(testData, subscriber2.getData());
        assertEquals(testData, receivedData2.get());
    }

    @Test
    public void testSubscriberUnregisters() {
        Publisher<String> publisher = new Publisher<>();

        AtomicReference<String> receivedData = new AtomicReference<>();
        Consumer<String> consumer = data -> receivedData.set(data);
        Runnable stopUpdateRunnable = () -> {};

        Subscriber<String> subscriber = new Subscriber<>(consumer, stopUpdateRunnable);
        subscriber.register(publisher);

        String initialData = "Initial Data";
        publisher.produce(initialData);

        subscriber.unregister();

        String newData = "New Data";
        publisher.produce(newData);

        assertEquals(initialData, subscriber.getData());
        assertEquals(initialData, receivedData.get());
    }

    @Test
    public void testPublisherStopService() {
        Publisher<String> publisher = new Publisher<>();

        AtomicBoolean stopUpdateCalled = new AtomicBoolean(false);
        Consumer<String> consumer = data -> {};
        Runnable stopUpdateRunnable = () -> stopUpdateCalled.set(true);

        Subscriber<String> subscriber = new Subscriber<>(consumer, stopUpdateRunnable);
        subscriber.register(publisher);

        publisher.close();

        assertTrue(stopUpdateCalled.get());
    }

    @Test
    public void testStopUpdateRunnableCalledOnUnregister() {
        Publisher<String> publisher = new Publisher<>();

        AtomicBoolean stopUpdateCalled = new AtomicBoolean(false);
        Consumer<String> consumer = data -> {};
        Runnable stopUpdateRunnable = () -> stopUpdateCalled.set(true);

        Subscriber<String> subscriber = new Subscriber<>(consumer, stopUpdateRunnable);
        subscriber.register(publisher);

        subscriber.unregister();

        assertTrue(stopUpdateCalled.get());
    }
}

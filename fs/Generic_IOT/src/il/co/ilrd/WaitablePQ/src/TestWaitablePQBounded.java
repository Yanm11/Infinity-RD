package il.co.ilrd.WaitablePQ.src;

import org.junit.*;

import java.util.concurrent.TimeUnit;

import static org.junit.Assert.*;

public class TestWaitablePQBounded {
    private WaitablePQBounded<Movie> boundedPQueueComparable;
    private WaitablePQBounded<Movie> boundedPQueueComparator;
    private final int capacity = 2;

    @Before
    public void setUp() {
        boundedPQueueComparable = new WaitablePQBounded<>(capacity);
        boundedPQueueComparator = new WaitablePQBounded<>(capacity, new CompareByRating());
    }

    @Test
    public void enqueueDequeueWithinCapacity() {
        Movie a = new Movie("A", 2002, 5);
        Movie b = new Movie("B", 2001, 4);

        boundedPQueueComparable.enqueue(a);
        boundedPQueueComparable.enqueue(b);

        assertEquals(b, boundedPQueueComparable.dequeue()); // b comes before a
        assertEquals(a, boundedPQueueComparable.dequeue());

        assertTrue(boundedPQueueComparable.isEmpty());
    }

    @Test
    public void testBlockingEnqueueWhenFull() throws InterruptedException {
        Movie a = new Movie("A", 2002, 5);
        Movie b = new Movie("B", 2001, 4);
        Movie c = new Movie("C", 2005, 3);

        boundedPQueueComparable.enqueue(a);
        boundedPQueueComparable.enqueue(b);

        Thread dequeueThread = new Thread(() -> {
            try {
                Thread.sleep(2000);
                boundedPQueueComparable.dequeue();
            } catch (Exception ignored) {
            }
        });
        dequeueThread.start();
        long startTime = System.nanoTime();
        boundedPQueueComparable.enqueue(c);
        long endTime = System.nanoTime();
        long elapsedTime = TimeUnit.NANOSECONDS.toMillis(endTime - startTime);
        assertTrue(elapsedTime >= 2000);
    }

    @Test
    public void testDequeueBlockingWhenEmpty() throws InterruptedException {
        Movie a = new Movie("A", 2002, 5);

        Thread equeueThread = new Thread(() -> {
            try {
                Thread.sleep(2000);
                boundedPQueueComparable.enqueue(a);
            } catch (Exception ignored) {
            }
        });

        equeueThread.start();
        long startTime = System.nanoTime();
        boundedPQueueComparable.dequeue();
        long endTime = System.nanoTime();
        long elapsedTime = TimeUnit.NANOSECONDS.toMillis(endTime - startTime);
        assertTrue(elapsedTime >= 2000);
    }

    @Test
    public void testRemove() {
        Movie a = new Movie("A", 2002, 5);
        Movie b = new Movie("B", 2001, 4);
        Movie c = new Movie("C", 2005, 3);

        boundedPQueueComparable.enqueue(a);
        boundedPQueueComparable.enqueue(b);

        assertTrue(boundedPQueueComparable.remove(b)); // Removes b
        assertEquals(a, boundedPQueueComparable.dequeue()); // Now only a is left
        assertFalse(boundedPQueueComparable.remove(c)); // c is not in the queue
    }

    @Test
    public void testPeek() throws Exception {
        Movie a = new Movie("A", 2002, 5);
        Movie b = new Movie("B", 2001, 4);

        boundedPQueueComparable.enqueue(a);
        boundedPQueueComparable.enqueue(b);

        assertEquals(b, boundedPQueueComparable.peek()); // Peek should return b (higher priority)
        assertEquals(b, boundedPQueueComparable.dequeue()); // Dequeue b
        assertEquals(a, boundedPQueueComparable.peek()); // Now a is at the head
    }
}

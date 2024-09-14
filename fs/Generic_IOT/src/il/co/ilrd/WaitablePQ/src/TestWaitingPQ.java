package il.co.ilrd.WaitablePQ.src;

import org.junit.*;
import java.util.concurrent.TimeUnit;
import static org.junit.Assert.*;

public class TestWaitingPQ {

    private WaitablePQ<Movie> waitablePQueueComparable = new WaitablePQ<>();
    private WaitablePQ<Movie> waitablePQueueComparator = new WaitablePQ<>(new CompareByRating());

    @Before
    public void setUp(){
        waitablePQueueComparable = new WaitablePQ<>();
        waitablePQueueComparator = new WaitablePQ<>(new CompareByRating());
    }

    @Test
    public void size(){
        assertEquals(0, waitablePQueueComparable.size());
        assertTrue(waitablePQueueComparable.isEmpty());
        waitablePQueueComparable.enqueue(new Movie("A", 1999, 5));
        assertEquals(1, waitablePQueueComparable.size());
        waitablePQueueComparable.enqueue(new Movie("B", 2000, 5));
        assertEquals(2, waitablePQueueComparable.size());
        waitablePQueueComparable.dequeue();
        assertEquals(1, waitablePQueueComparable.size());
        waitablePQueueComparable.dequeue();
        assertEquals(0, waitablePQueueComparable.size());
    }

    @Test
    public void isEmpty(){
        assertEquals(0, waitablePQueueComparable.size());
        assertTrue(waitablePQueueComparable.isEmpty());
        waitablePQueueComparable.enqueue(new Movie("A", 1999, 5));
        assertFalse(waitablePQueueComparable.isEmpty());
    }

    @Test
    public void enqueue(){
        Movie a = new Movie("A", 2002, 5);
        Movie b = new Movie("B", 2001, 4);
        Movie c = new Movie("C", 2005, 3);

        waitablePQueueComparable.enqueue(a);
        waitablePQueueComparable.enqueue(b);
        waitablePQueueComparable.enqueue(c);

        assertEquals(b, waitablePQueueComparable.dequeue());
        assertEquals(a, waitablePQueueComparable.dequeue());
        assertEquals(c, waitablePQueueComparable.dequeue());

        waitablePQueueComparator.enqueue(a);
        waitablePQueueComparator.enqueue(b);
        waitablePQueueComparator.enqueue(c);

        assertEquals(c, waitablePQueueComparator.dequeue());
        assertEquals(b, waitablePQueueComparator.dequeue());
        assertEquals(a, waitablePQueueComparator.dequeue());
    }

    @Test
    public void dequeue() {
        Movie a = new Movie("A", 2002, 5);
        Movie b = new Movie("B", 2001, 4);

        waitablePQueueComparable.enqueue(a);
        waitablePQueueComparable.enqueue(b);

        assertEquals(b, waitablePQueueComparable.dequeue()); // Natural order: b comes before a
        assertEquals(a, waitablePQueueComparable.dequeue());
        assertTrue(waitablePQueueComparable.isEmpty());

        waitablePQueueComparator.enqueue(a);
        waitablePQueueComparator.enqueue(b);

        assertEquals(b, waitablePQueueComparator.dequeue()); // Custom comparator by rating: b comes first
        assertEquals(a, waitablePQueueComparator.dequeue());
    }


    @Test
    public void remove() {
        Movie a = new Movie("A", 2002, 5);
        Movie b = new Movie("B", 2001, 4);
        Movie c = new Movie("C", 2005, 3);

        waitablePQueueComparable.enqueue(a);
        waitablePQueueComparable.enqueue(b);
        waitablePQueueComparable.enqueue(c);

        assertTrue(waitablePQueueComparable.remove(b)); // Removes b
        assertEquals(a, waitablePQueueComparable.dequeue()); // a comes before c
        assertEquals(c, waitablePQueueComparable.dequeue()); // Now c
        assertTrue(waitablePQueueComparable.isEmpty());

        // Test removal of non-existent element
        assertFalse(waitablePQueueComparable.remove(b)); // b is not in the queue anymore
    }

    @Test
    public void peek() {
        Movie a = new Movie("A", 2002, 5);
        Movie b = new Movie("B", 2001, 4);

        waitablePQueueComparable.enqueue(a);
        waitablePQueueComparable.enqueue(b);

        assertEquals(b, waitablePQueueComparable.peek()); // b comes first
        assertEquals(b, waitablePQueueComparable.dequeue()); // Then dequeue b
        assertEquals(a, waitablePQueueComparable.peek()); // Now a is at the head
    }

    @Test
    public void peekEmptyQueue() {
        assertNull(waitablePQueueComparable.peek()); // Empty queue, peek should return null
    }
}


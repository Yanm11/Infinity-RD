package il.co.ilrd.WaitablePQ.src;

import java.util.PriorityQueue;
import java.util.Comparator;
import java.util.concurrent.Semaphore;

public class WaitablePQ<E> {
    private PriorityQueue<E> pq;
    private Semaphore elemInQueueSem = new Semaphore(0);

    public WaitablePQ() {
        pq = new PriorityQueue<>();
    }

    public WaitablePQ(Comparator<E> comparator) {
        pq = new PriorityQueue<>(comparator);
    }

    public void enqueue(E element) {
        synchronized (pq) {
            pq.add(element);
        }

        // increasing the number of elements in queue and updating the semaphore
        elemInQueueSem.release();
    }

    public E dequeue() {
        try {
            elemInQueueSem.acquire();
        }
        catch (InterruptedException ignored) {}

        synchronized (pq) {
            return pq.poll();
        }
    }

//    public E dequeue(long timeout, TimeUnit unit) {}

    synchronized public boolean remove(E element) {
        boolean foundAndRemoved;

        synchronized (pq) {
            foundAndRemoved = pq.remove(element);
        }

        if (foundAndRemoved) {
             try {
                 elemInQueueSem.acquire();
             }
             catch (InterruptedException ignored) {}

             return true;
         }

        return false;
    }

//    public boolean remove(E element, long timeout, TimeUnit unit) {}

    public E peek() {
        synchronized (pq) {
            return pq.peek();
        }
    }

    public int size() {
        synchronized (pq) {
            return pq.size();
        }
    }

    public boolean isEmpty() {
        synchronized (pq) {
            return pq.isEmpty();
        }
    }
}

package il.co.ilrd.WaitablePQ.src;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.concurrent.locks.*;

public class WaitablePQBounded<E> {
    private PriorityQueue<E> pq;
    private final Lock lock = new ReentrantLock();
    private final Condition notFull  = lock.newCondition();
    private final Condition notEmpty = lock.newCondition();
    private final int capacity;

    public WaitablePQBounded(int capacity) {
        this(capacity, null);
    }

    public WaitablePQBounded(int capacity, Comparator<E> comparator) {
        if (capacity <= 0) {
            throw new IllegalArgumentException("Capacity must be greater than 0");
        }

        pq = new PriorityQueue<>(comparator);
        this.capacity = capacity;
    }

    public void enqueue(E element) {
        lock.lock();
        try {
            while (pq.size() == capacity) {
                notFull.await();
            }

            pq.add(element);

            notEmpty.signalAll();
        }

        catch (InterruptedException ignored) {}

        finally {
            lock.unlock();
        }
    }

    public E dequeue() {
        E result = null;

        lock.lock();
        try {
            while (pq.isEmpty()) {
                notEmpty.await();
            }

            result =  pq.poll();

            notFull.signalAll();
        }

        catch (InterruptedException ignored) {}

        finally {
            lock.unlock();
        }

        return result;
    }

//    public E dequeue(long timeout, TimeUnit unit) {}

    synchronized public boolean remove(E element) {
        lock.lock();
        try{
            boolean hadRemoved = pq.remove(element);
            if (hadRemoved) {
                notFull.signalAll();
            }

         return hadRemoved;
        }
         finally {
            lock.unlock();
        }
    }

//    public boolean remove(E element, long timeout, TimeUnit unit) {}

    public E peek() {
        lock.lock();
        try {
            return pq.peek();
        }
        finally {
            lock.unlock();
        }
    }

    public int size() {
        lock.lock();
        try {
            return pq.size();
        }
        finally {
            lock.unlock();
        }
    }

    public boolean isEmpty() {
        lock.lock();
        try {
            return pq.isEmpty();
        }
        finally {
            lock.unlock();
        }
    }
}

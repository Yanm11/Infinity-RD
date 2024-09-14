package il.co.ilrd.ThreadPool.src;

import org.junit.Before;
import org.junit.Test;

import java.util.ArrayList;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.atomic.AtomicInteger;
import static org.junit.Assert.*;
import java.util.concurrent.Callable;

public class ThreadPoolTest {
    ThreadPool threadPool;
    AtomicInteger counter;
    Runnable runnableTask;
    Callable<Integer> callableTask;

    @Before
    public void setUp() {
        threadPool = new ThreadPool(5);
        counter = new AtomicInteger(1);

        // Runnable that prints the order number
        runnableTask = () -> {
            int order = counter.getAndIncrement();
            System.out.println("Runnable executed with order: " + order);
        };

        // Callable that prints the order number and returns it
        callableTask = () -> {
            int order = counter.getAndIncrement();
            System.out.println("Callable executed with order: " + order);
            return order;
        };
    }

    @Test
    public void execute() {
        for (int i = 0; i < 10; ++i) {
            threadPool.execute(runnableTask);
        }
    }

    @Test
    public void submit() {
        ArrayList<Future<?>> futures = new ArrayList<>();

        for (int i = 0; i < 10; ++i) {
            Future<?> future =  threadPool.submit(runnableTask);
            futures.add(future);
        }

        for (int i = 0; i < 10; ++i) {
            System.out.println("getting the future: "+i);
            try {
                assertNull(futures.get(i).get());
            }
            catch (InterruptedException | ExecutionException ignored){}
        }
    }

    @Test
    public void testSubmit() {
    }

    @Test
    public void testSubmit1() {
    }

    @Test
    public void testSubmit2() {
    }

    @Test
    public void testSubmit3() {
    }

    @Test
    public void setNumOfThreads() {
    }
}
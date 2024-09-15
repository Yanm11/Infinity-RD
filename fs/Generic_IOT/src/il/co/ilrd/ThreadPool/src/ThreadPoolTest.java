package il.co.ilrd.ThreadPool.src;

import org.junit.*;
import org.junit.runners.MethodSorters;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;
import static java.lang.Thread.sleep;
import static org.junit.Assert.*;

@FixMethodOrder(MethodSorters.NAME_ASCENDING)
public class ThreadPoolTest {
    private static Monitor monitor = new Monitor();
    private static String message = "message";
    private static int messageNumber;

    @Test
    public void a_testCreatePool(){
        ThreadPool threadPool = new ThreadPool(3);
        threadPool.shutdown();
    }

    @Test
    public void b_testSubmitRunnable() throws ExecutionException, InterruptedException {
        ThreadPool threadPool = new ThreadPool(1);
        Future<?> future = threadPool.submit(()-> monitor.writeMessage("runnable task 1"));
        assertNull(future.get());
        assertEquals("runnable task 1", monitor.getLastMessage());
        Future<String> future1 = threadPool.submit(()->doNothing(), Priority.HIGH, message + ++messageNumber);
        assertEquals("message1", future1.get());
        threadPool.shutdown();
    }

    @Test
    public void c_testSubmitCallable() throws ExecutionException, InterruptedException {
        ThreadPool threadPool = new ThreadPool(1);
        Future<String > future = threadPool.submit(()-> message + ++messageNumber);
        assertEquals("message2", future.get());
        assertEquals(threadPool.submit(()->20).get(), Integer.valueOf(20));
        threadPool.shutdown();
    }

    @Test
    public void d_testPriority() throws ExecutionException, InterruptedException {
        ThreadPool threadPool = new ThreadPool(1);
        for (int i = 0; i < 3; i++) {
            threadPool.submit(()->{
                try {
                    sleep(1500);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                ++messageNumber;
                monitor.writeMessage(message + " low");
            }, Priority.LOW);
        }
        threadPool.submit(()->{
            ++messageNumber;
            monitor.writeMessage(message + " high");
        }, Priority.HIGH);

        threadPool.shutdown();
        threadPool.awaitTermination();
        assertEquals(6, messageNumber);
        assertEquals("message low", monitor.getLastMessage());
    }

    @Test
    public void e_setNumOfThreads() throws InterruptedException {
        Callable<Void> callable = () -> {
            sleep(1000);
            return null;
        };
        ThreadPool threadPool = new ThreadPool(1);
        long startTime = System.nanoTime();
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.setNumOfThreads(3);
        threadPool.shutdown();
        threadPool.awaitTermination();
        long endTime = System.nanoTime();
        long elapsedTime = TimeUnit.NANOSECONDS.toMillis(endTime - startTime);
        assertTrue(3000 >= elapsedTime);

        threadPool = new ThreadPool(3);
        threadPool.setNumOfThreads(1);
        startTime = System.nanoTime();
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);

        threadPool.shutdown();
        threadPool.awaitTermination();
        endTime = System.nanoTime();
        elapsedTime = TimeUnit.NANOSECONDS.toMillis(endTime - startTime);
        assertTrue(6000 <= elapsedTime);
    }

    @Test
    public void f_testPauseResume() throws InterruptedException {
        Callable<Void> callable = () -> {
            ++messageNumber;
            return null;
        };
        ThreadPool threadPool = new ThreadPool(1);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        sleep(1000);
        threadPool.pause();
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        sleep(1000);
        assertEquals(12, messageNumber);

        threadPool.resume();
        threadPool.shutdown();
        threadPool.awaitTermination();
        assertEquals(16, messageNumber);
    }

    @Test
    public void g_testAwait() throws InterruptedException {
        Callable<Void> callable = () -> {
            sleep(1000);
            ++messageNumber;
            return null;
        };
        ThreadPool threadPool = new ThreadPool(1);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);

        threadPool.shutdown();
        threadPool.awaitTermination();
        assertEquals(20, messageNumber);
    }

    @Test
    public void h_testAwaitWithTime() throws InterruptedException {
        Callable<Void> callable = () -> {
            sleep(1000);
            return null;
        };
        ThreadPool threadPool = new ThreadPool(1);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);
        threadPool.submit(callable);

        threadPool.shutdown();
        assertFalse(threadPool.awaitTermination(3, TimeUnit.SECONDS));
        assertTrue(threadPool.awaitTermination(2, TimeUnit.SECONDS));
    }

    @Test
    public void i_testFutureCancel() throws InterruptedException {
        Callable<Void> callable = () -> {
            sleep(1000);
            return null;
        };
        ThreadPool threadPool = new ThreadPool(1);
        Future<Void> future = threadPool.submit(callable);
        sleep(500);
        assertFalse(future.cancel(true));
        Future<Void> future2 = threadPool.submit(callable);
        Future<Void> future3 = threadPool.submit(callable);
        Future<Void> future4 = threadPool.submit(callable);
        assertTrue(future2.cancel(true));
        assertTrue(future3.cancel(true));
        assertTrue(future4.cancel(true));
        assertFalse(future4.cancel(true));
        assertFalse(future.cancel(true));

        assertFalse(future.isCancelled());
        assertTrue(future2.isCancelled());
        assertTrue(future3.isCancelled());
        assertTrue(future4.isCancelled());

        threadPool.shutdown();
        threadPool.awaitTermination();
    }

    @Test
    public void j_testFutureIsDone() throws InterruptedException {
        Callable<Void> callable = () -> {
            sleep(1000);
            return null;
        };
        ThreadPool threadPool = new ThreadPool(1);
        Future<Void> future = threadPool.submit(callable);
        assertFalse(future.isDone());
        sleep(1200);
        assertTrue(future.isDone());
        Future<Void> future2 = threadPool.submit(callable);
        Future<Void> future3 = threadPool.submit(callable);
        future2.cancel(true);
        assertTrue(future2.isDone());

        threadPool.shutdown();
        threadPool.awaitTermination();
    }

    @Test
    public void k_testFutureGet() throws InterruptedException, ExecutionException {
        ThreadPool threadPool = new ThreadPool(1);
        Future<String> future1 = threadPool.submit(()->"String");
        Future<Integer> future2 = threadPool.submit(()-> 13 + 5);
        Future<Double> future3 = threadPool.submit(()-> 4.12);
        String s = future1.get();
        Integer i = future2.get();
        Double d = future3.get();
        assertEquals(s, "String");
        assertEquals(Integer.valueOf(18), i);
        assertEquals(Double.valueOf(4.12), d);

        threadPool.shutdown();
        threadPool.awaitTermination();
    }

    @Test
    public void l_testFutureGetWithTime() throws InterruptedException, ExecutionException, TimeoutException {
        ThreadPool threadPool = new ThreadPool(1);
        Future<String> future1 = threadPool.submit(()->{
            sleep(2000);
            return "String";
        });
        String s = future1.get(3, TimeUnit.SECONDS);
        assertEquals(s, "String");

        threadPool.shutdown();
        threadPool.awaitTermination();
    }

    @Test
    public void m_testException() throws InterruptedException {
        ThreadPool threadPool = new ThreadPool(1);
        assertThrows(IllegalArgumentException.class, ()->new ThreadPool(0));
        assertThrows(IllegalArgumentException.class, () -> new ThreadPool(-1));
        assertThrows(NullPointerException.class, () -> threadPool.submit((Runnable) null));
        assertThrows(NullPointerException.class, () -> threadPool.submit((Callable<?>) null));
        assertThrows(NullPointerException.class, () -> threadPool.submit((Runnable) null, Priority.HIGH));
        assertThrows(NullPointerException.class, () -> threadPool.submit((Callable<?>) null, Priority.HIGH));
        assertThrows(IllegalArgumentException.class, ()->threadPool.setNumOfThreads(0));

        threadPool.submit(()-> {
            try {
                sleep(1000);
            } catch (InterruptedException ignored) {}
        });
        Future<Void> future2 = threadPool.submit(()->null);
        future2.cancel(true);
        assertThrows(CancellationException.class, future2::get);

        Future<?> futureWithException = threadPool.submit(() -> {
            throw new RuntimeException("Test Exception");
        });
        assertThrows(ExecutionException.class, futureWithException::get);

        Future<Void> longRunningTask = threadPool.submit(() -> {
            try {
                Thread.sleep(2000); // Simulate long task
            } catch (InterruptedException ignored) {}
            return null;
        });
        assertThrows(TimeoutException.class, () -> longRunningTask.get(1, TimeUnit.SECONDS));  // Timeout of 1 second

        Future<?> future = threadPool.submit(() -> {
            try {
                Thread.sleep(3000);  // Simulate long task
            } catch (InterruptedException ignored) {}
        });


        Thread.currentThread().interrupt(); // Simulate interruption
        assertThrows(InterruptedException.class, future::get);

        threadPool.shutdown();
        threadPool.awaitTermination();
        assertThrows(RejectedExecutionException.class, () -> threadPool.submit(() -> System.out.println("Task after shutdown")));
    }

    private void doNothing(){}

    private static class Monitor{
        private List<String> history = new ArrayList<>();
        private String lastMessage;

        public void writeMessage(String s){
            lastMessage = s;
            history.add(s);
        }

        public String getLastMessage() {
            return lastMessage;
        }
    }
}

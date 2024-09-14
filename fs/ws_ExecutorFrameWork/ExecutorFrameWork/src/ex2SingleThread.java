import java.util.ArrayList;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;

public class ex2SingleThread {
    public static void main(String[] args) {
        Integer result = null;
        int numberOfThreads = 5;
        Future<Integer> future = null;
        ArrayList<Future<Integer>> futuresList = new ArrayList<>();
        AtomicInteger global = new AtomicInteger(0);

        // creating the task
        Callable<Integer> task = () -> {
            System.out.println("Task started...");
            Thread.sleep(5000);
            global.incrementAndGet();
            int g = global.get();
            return g;
        };
        //ex2 single thread pool
        //ExecutorService executorService = Executors.newFixedThreadPool(1);
        //ex2 3 threads thread pool
        //ExecutorService executorService = Executors.newFixedThreadPool(3);
        //ex2 cached thread pool
        //ExecutorService executorService = Executors.newCachedThreadPool();
        //ex2 single thread pool
        ScheduledExecutorService executorService = Executors.newScheduledThreadPool(3);

        for (int i = 0; i < numberOfThreads; ++i) {
            future = executorService.submit(task);
            //future = executorService.schedule(task,1, TimeUnit.SECONDS);
            futuresList.add(future);
        }

        for (int i = 0; i < numberOfThreads; ++i) {
            try {
                result = futuresList.get(i).get();  // Blocks until task is completed
            } catch (InterruptedException | ExecutionException ignored) {
            }

            System.out.println(result);
        }
        executorService.shutdown();
    }
}



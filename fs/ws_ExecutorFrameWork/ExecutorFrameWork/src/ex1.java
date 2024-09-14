import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.ExecutionException;

public class ex1 {
    public static void main(String[] args) {
        String result = null;

        ExecutorService executorService = Executors.newSingleThreadExecutor();

        Callable<String> task = () -> {
            System.out.println("Task started...");
            Thread.sleep(2000);  // Simulate some delay (task is doing work)
            return "Task completed";
        };

        Future<String> future = executorService.submit(task);
        try {
            result = future.get();  // Blocks until task is completed
        }
        catch (InterruptedException | ExecutionException ignored) {}

        System.out.println(result);

        executorService.shutdown();
    }
}

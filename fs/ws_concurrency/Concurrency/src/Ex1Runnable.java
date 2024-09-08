public class Ex1Runnable {
    public static void main(String[] args) {
        // Creating a runnable task
        Runnable task = new Runnable() {
            @Override
            public void run() {
                System.out.println("Task started using Runnable.");
                try {
                    // Simulating some task
                    Thread.sleep(3000);
                } catch (InterruptedException e) {
                    System.out.println("Task was interrupted.");
                }
                System.out.println("Task stopped using Runnable.");
            }
        };

        // Wrapping the runnable task inside a Thread
        Thread taskThread = new Thread(task);

        // Starting the task
        taskThread.start();

        // Stopping the task (wait for it to finish or interrupt)
        try {
            taskThread.join();  // Waiting for the thread to finish
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Main thread completed.");
    }


}

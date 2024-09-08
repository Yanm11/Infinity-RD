public class ex1 {
    public static void main(String[] args) {
        // Creating a thread using java.lang.Thread class
        Thread taskThread = new Thread() {
            @Override
            public void run() {
                System.out.println("Task started using Thread.");
                try {
                    // Simulating some task
                    Thread.sleep(3000);
                } catch (InterruptedException e) {
                    System.out.println("Task was interrupted.");
                }
                System.out.println("Task stopped using Thread.");
            }
        };

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

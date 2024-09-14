package il.co.ilrd.ThreadPool.src;

import java.util.concurrent.*;
import il.co.ilrd.WaitablePQ.src.WaitablePQ;
import java.lang.Thread;

public class ThreadPool implements Executor {
    //private fileds
    private WaitablePQ<Task<?>> taskPQ;
    private int numberOfThreads;
    private boolean stopRun = false;

    //ctor
    // Default numberOfThreads depend on number of cores
    public ThreadPool() {
        this(Runtime.getRuntime().availableProcessors());
    }

    //receives the original number of threads
    public ThreadPool(int numberOfThreads) {
        taskPQ = new WaitablePQ<>();
        this.numberOfThreads = numberOfThreads;

        //creating new threads and assigning them the first task
        createNewThreads(numberOfThreads);
    }

    //add task methods
    @Override
    public void execute(Runnable command) {
        submit(command, Priority.MEDIUM, (Void) null);
    }

    public Future<Void> submit(Runnable command){
        return submit(command, Priority.MEDIUM, null);
    }

    public Future<Void> submit(Runnable command, Priority p){
        return submit(command, p, null);
    }

    public <T> Future<T> submit(Runnable command, Priority p, T value){
        // wrap a runnable inside a callable
        Callable<T> callable = new Callable<T>() {
            @Override
            public T call() throws Exception {
                command.run();

                return value;
            }
        };

        return enqueueTask(callable, p.getValue());
    }

    public <T> Future<T> submit(Callable<T> command){
        return submit(command, Priority.MEDIUM);
    }


    public <T> Future<T> submit(Callable<T> command, Priority p){
        return enqueueTask(command, p.getValue());
    }

    // setter
    // if threads are removed, they should be the first threads that not running
    public void setNumOfThreads(int numOfThreads) {
        if (numOfThreads > this.numberOfThreads) {
            createNewThreads(numOfThreads - this.numberOfThreads);
        }
        else if (numOfThreads < this.numberOfThreads) {
            Callable<Void> command = new Callable<Void>() {
                @Override
                public Void call() throws Exception {
                    stopRun = true;

                    return null;
                }
            };

            int threadsToRemove = this.numberOfThreads - numOfThreads;
            for (int i = 0; i < threadsToRemove; ++i) {
                enqueueTask(command, Priority.HIGH.getValue() + 1);
            }
        }

        this.numberOfThreads = numOfThreads;
    }

    //operations
    public void pause(){}
    public void resume(){}
    public void shutdown(){}
    public void awaitTermination(){}
    public boolean awaitTermination(long timeout,TimeUnit unit){return true;}

    // helper function
    private <T> Future<T> enqueueTask(Callable<T> command, int priority) {
        // adding a new task to the queue
        Task<T> task = new Task<>(command, priority);
        taskPQ.enqueue(task);

        return task.getFuture();
    }
    private void createNewThreads(int numberOfThreads) {
        //creating new threads and assigning them the first task
        for (int i = 0; i < numberOfThreads; ++i) {
            Thread thread = new Thread() {
                @Override
                public void run() {
                    while (!stopRun) {
                        Task<?> task = taskPQ.dequeue();
                        task.executeTask();
                    }
                }
            };
            thread.start();
        }
    }

    private class Task<E> implements Comparable<Task<E>> {
        private final Callable<E> command;
        private final int priority;
        private final Future<E> future;
        private boolean hadStarted = false;
        private boolean hadException = false;
        private boolean completed = false;
        private E result = null;

        public Task(Callable<E> command, int priority) {
            this.command = command;
            this.priority = priority;
            future = new TaskFuture();
        }

        @Override
        public int compareTo(Task<E> task){
            return (task.getPriority() - this.priority);
        }

        // helper function
        public int getPriority(){
            return this.priority;
        }

        public Future<E> getFuture() {
            return future;
        }

        public Callable<E> getCommand() {
            return this.command;
        }

        synchronized public void executeTask() {
            try {
                hadStarted = true;
                 result = command.call();
            }
            catch (Exception e){
                hadException = true;
            }

            finally {
                completed = true;
                notifyAll();
            }
        }

        private class TaskFuture implements Future<E> {
            private boolean cancelled = false;

            @Override
            public boolean cancel(boolean mayInterruptIfRunning) {
                if (completed || cancelled) {
                    return false;
                }
                else if (hadStarted && mayInterruptIfRunning) {
                    // send interrupt to do..
                }
                //cancel the execution of the task by removing it from the queue
                cancelled = taskPQ.remove(Task.this);
                completed = cancelled;

                return cancelled;

            }

            @Override
            public boolean isCancelled() {
                return cancelled;
            }

            @Override
            public boolean isDone() {
                return completed;
            }

            @Override
            synchronized public E get() throws InterruptedException, ExecutionException {
                while (!completed && !cancelled) {
                    wait();

                    if (Thread.interrupted()) {
                        throw new InterruptedException("Task was interrupted");
                    }
                }

                if (cancelled) {
                    throw new CancellationException("Task was canceled");
                }
                else if (hadException) {
                    throw new ExecutionException(new Exception("Task had an exception"));
                }

                return result;
            }

            @Override
            synchronized public E get(long timeout, TimeUnit unit) throws InterruptedException, ExecutionException, TimeoutException {
                long endTime = System.currentTimeMillis() + unit.toMillis(timeout);
                boolean passedTimeout = System.currentTimeMillis() > endTime;

                while (!completed && !cancelled && !passedTimeout) {
                    wait();

                    if (Thread.interrupted()) {
                        throw new InterruptedException("Task was interrupted");
                    }

                    passedTimeout = System.currentTimeMillis() > endTime;
                }

                if (cancelled) {
                    throw new CancellationException("Task was canceled");
                }
                else if (passedTimeout) {
                    throw new TimeoutException("Task timed out");
                }
                else if (hadException) {
                    throw new ExecutionException(new Exception("Task had an exception"));
                }

                return result;
            }
        }
    }
}



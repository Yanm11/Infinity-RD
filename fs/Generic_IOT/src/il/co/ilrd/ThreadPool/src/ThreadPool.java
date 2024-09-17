package il.co.ilrd.ThreadPool.src;

import java.util.ArrayList;
import java.util.concurrent.*;
import il.co.ilrd.WaitablePQ.src.WaitablePQ;
import java.lang.Thread;

public class ThreadPool implements Executor {
    //private fileds
    private WaitablePQ<Task<?>> taskPQ;
    private int numberOfThreads;
    private boolean shutdown = false;
    private Semaphore pauseSem;
    private ArrayList<Future<Void>> shutDownFutures;

    //ctor
    // Default numberOfThreads depend on number of cores
    public ThreadPool() {
        this(Runtime.getRuntime().availableProcessors());
    }

    //receives the original number of threads
    public ThreadPool(int numberOfThreads) {
        //exception handling
        if (numberOfThreads <= 0) {
            throw new IllegalArgumentException();
        }

        taskPQ = new WaitablePQ<>();
        this.numberOfThreads = numberOfThreads;
        pauseSem = new Semaphore(numberOfThreads);

        //creating new threads and assigning them the first task
        startNewThreads(numberOfThreads);
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
        if (command == null) {
            throw new NullPointerException();
        }

        // wrap a runnable inside a callable
        Callable<T> callable = new Callable<T>() {
            @Override
            public T call() throws Exception {
                command.run();

                return value;
            }
        };

        return submit(callable, p);
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
        //exception handling
        if (numOfThreads <= 0) {
            throw new IllegalArgumentException();
        }

        //if we increase
        if (numOfThreads > this.numberOfThreads) {
            int increaseNumberOfThreadsBy = numOfThreads - this.numberOfThreads;
            pauseSem.release(increaseNumberOfThreadsBy);
            startNewThreads(increaseNumberOfThreadsBy);
        }
        //if we decrease
        else if (numOfThreads < this.numberOfThreads) {
            int threadsToRemove = this.numberOfThreads - numOfThreads;

            //inserting posiend apples to shut down the threads
            enqueuePoisonedTasks(threadsToRemove, Priority.HIGH.getValue() + 1);
        }

        //update num of threads
        this.numberOfThreads = numOfThreads;
    }

    //operations
    public void pause(){
        Callable<Void> sleepingPill = new Callable<Void>() {
            @Override
            public Void call() throws Exception {
                try {
                    pauseSem.acquire();
                }
                catch (InterruptedException ignored) {}

                return null;
            }
        };

        for (int i = 0; i < this.numberOfThreads; ++i) {
            enqueueTask(sleepingPill, Priority.HIGH.getValue() + 1);
        }
    }

    public void resume(){
        pauseSem.release(this.numberOfThreads);
    }

    public void shutdown(){
        //inserting poisoned pills to shut down the threads and keep a reference to their futures
        shutDownFutures =  enqueuePoisonedTasks(this.numberOfThreads, Priority.LOW.getValue() - 1);

        //rejecting new submissions
        this.shutdown = true;

        //updating number of threads
        this.numberOfThreads = 0;
    }

    public void awaitTermination() throws InterruptedException{
        try {
            for (Future<?> future : shutDownFutures) {
                future.get();
            }
        }
        catch (InterruptedException | ExecutionException e) {
            throw new InterruptedException();
        }
        catch (NullPointerException e) {
            throw new NullPointerException("did not call shut down before awaitTermination");
        }
    }

    public boolean awaitTermination(long timeout,TimeUnit unit) throws InterruptedException {
        long endTime = System.currentTimeMillis() + unit.toMillis(timeout);

        try {
            for (Future<?> future : shutDownFutures) {
                future.get(endTime - System.currentTimeMillis(), TimeUnit.MILLISECONDS);
            }
        }
        catch (InterruptedException | ExecutionException e) {
            throw new InterruptedException();
        }
        catch (TimeoutException e) {
            return false;
        }
        catch (NullPointerException e) {
            throw new NullPointerException("did not call shut down before awaitTermination");
        }
        return true;
    }

    /* ********************************************* helper function *********************************************** */
    private <T> Future<T> enqueueTask(Callable<T> command, int priority) {
        return enqueueTask(command,priority,false);
    }

    //overloading
    private <T> Future<T> enqueueTask(Callable<T> command, int priority, boolean isPoisoned) {
        if (command == null) {
            throw new NullPointerException();
        }

        if (shutdown) {
            throw new RejectedExecutionException("Can not enqueue new tasks...shutdown initiated");
        }

        // adding a new task to the queue
        Task<T> task = new Task<>(command, priority);
        task.setIsPoisoned(isPoisoned);
        taskPQ.enqueue(task);

        return task.getFuture();
    }

    private void startNewThreads(int numberOfThreads) {
        //creating new threads and assigning them the first task
        for (int i = 0; i < numberOfThreads; ++i) {
            Thread thread = new Thread() {
                @Override
                public void run() {
                    try {
                        pauseSem.acquire();
                    }
                    catch (InterruptedException e) {
                        throw new RuntimeException();
                    }

                    boolean isPoisoned = false;
                    while (!isPoisoned) {
                        Task<?> task = taskPQ.dequeue();
                        task.executeTask();
                        isPoisoned = task.getIsPoisoned();
                    }
                }
            };
            thread.start();
        }
    }

    private ArrayList<Future<Void>> enqueuePoisonedTasks(int numberOfThreadsToKill,int priority) {
        //instancing an empty command
        Callable<Void> command = new Callable<Void>() {
            @Override
            public Void call() throws Exception {
                return null;
            }
        };

        //enqueue the tasks
        ArrayList<Future<Void>> futures = new ArrayList<>();
        for (int i = 0; i < numberOfThreadsToKill; ++i) {
            futures.add(enqueueTask(command, priority, true));
        }

        return futures;
    }
    /* ************************************************************************************************************* */

    private class Task<E> implements Comparable<Task<E>> {
        // Main instance variables
        private final Callable<E> command;
        private final int priority;
        private final Future<E> future;
        private E result = null;

        // Flags
        private boolean hadStarted = false;
        private boolean hadException = false;
        private boolean completed = false;
        private boolean isPoisoned = false;

        // Synchronization
        private final Object lock = new Object();
        private Thread currThread = null;

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

        public boolean getIsPoisoned() {
            return isPoisoned;
        }

        public void setIsPoisoned(boolean isPoisoned) {
            this.isPoisoned = isPoisoned;
        }

        public void executeTask() {
            synchronized (lock) {
                try {
                    hadStarted = true;
                    currThread = Thread.currentThread();
                    result = command.call();
                } catch (Exception e) {
                    hadException = true;
                } finally {
                    completed = true;
                    lock.notifyAll();
                }
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
                    currThread.interrupt();
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
            public E get() throws InterruptedException, ExecutionException {
               synchronized (lock) {
                   while (!completed && !cancelled) {
                       lock.wait();
                   }
               }

               if (Thread.interrupted()) {
                   throw new InterruptedException("Task was interrupted");
               }
                if (cancelled) {
                    throw new CancellationException("Task was canceled");
                }
                if (hadException) {
                    throw new ExecutionException(new Exception("Task had an exception"));
                }

                return result;
            }

            @Override
            public E get(long timeout, TimeUnit unit) throws InterruptedException, ExecutionException, TimeoutException {
                long endTime = System.currentTimeMillis() + unit.toMillis(timeout);

                synchronized (lock) {
                    while (!completed && !cancelled && System.currentTimeMillis() <= endTime) {
                        lock.wait(endTime - System.currentTimeMillis());
                    }
                }

                if (Thread.interrupted()) {
                    throw new InterruptedException("Task was interrupted");
                }
                if (cancelled) {
                    throw new CancellationException("Task was canceled");
                }
                if (System.currentTimeMillis() > endTime) {
                    throw new TimeoutException("Task timed out");
                }
                if (hadException) {
                    throw new ExecutionException(new Exception("Task had an exception"));
                }

                return result;
            }
        }
    }
}



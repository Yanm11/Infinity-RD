package il.co.ilrd.Observer.src;

import java.util.function.Consumer;

public class Callback<T> {
    private Dispacher<T> dispacher;
    private Consumer<T> consumer;
    private Runnable stopUpdateRunnable;

    public Callback(Consumer<T> consumer, Runnable stopUpdateRunnable) {
        this.consumer = consumer;
        this.stopUpdateRunnable = stopUpdateRunnable;
    }

    public void update(T data) {
        consumer.accept(data);
    }

    public void stopUpdate() {
        stopUpdateRunnable.run();
    }

    public void setDispatcher(Dispacher<T> dispacher) {
        this.dispacher = dispacher;
    }

    public void unregister() {
        dispacher.unregister(this);
        setDispatcher(null);
    }
}

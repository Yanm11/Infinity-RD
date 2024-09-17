package il.co.ilrd.Observer.src;

import java.util.function.Consumer;

public class Subscriber<T> {
    private final Callback<T> callback;
    private T data;

    public Subscriber(Consumer<T> consumer, Runnable stopUpdateRunnable) {
        Consumer<T> defaultConsumer = (data) -> this.data = data;
        this.callback = new Callback<>(defaultConsumer.andThen(consumer), stopUpdateRunnable);
    }

    public void register(Publisher<T> publisher) {
        publisher.register(callback);
    }

    public void unregister() {
        callback.unregister();
    }

    public T getData() {
        return data;
    }
}







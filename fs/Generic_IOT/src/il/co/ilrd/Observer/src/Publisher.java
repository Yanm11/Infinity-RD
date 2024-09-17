package il.co.ilrd.Observer.src;

public class Publisher<T> {
    private Dispacher<T> dispacher = new Dispacher<>();

    public void register(Callback<T> callback) {
        dispacher.register(callback);
    }
    public void produce(T data) {
        dispacher.updateAll(data);
    }
    public void close() {
        dispacher.stopService();
    }
}

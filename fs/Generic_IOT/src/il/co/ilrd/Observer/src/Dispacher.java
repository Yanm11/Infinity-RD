package il.co.ilrd.Observer.src;

import java.util.ArrayList;

public class Dispacher<T> {
    private ArrayList<Callback<T>> callbacks = new ArrayList<>();

    public void register(Callback<T> callback) {
        callbacks.add(callback);
        callback.setDispatcher(this);
    }

    public void unregister(Callback<T> callback) {
        callbacks.remove(callback);
        callback.stopUpdate();
    }

    public void updateAll(T data) {
        for (Callback<T> callback : callbacks) {
            callback.update(data);
        }
    }

    public void stopService() {
        for (Callback<T> callback : callbacks) {
            callback.stopUpdate();
        }
        callbacks.clear();
    }
}

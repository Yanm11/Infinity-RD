package il.co.ilrd.Factory.src;

import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class Factory<K, T, D> {
    private final Map<K, Function<D, ? extends T>> functions = new HashMap<>();

    public T create(K key, D data) {
        if (functions.get(key) == null) {
            throw new IllegalArgumentException("Could not find key in functions hashmap");
        }

        return functions.get(key).apply(data);
    }

    public void add(K key, Function<D, ? extends T> func) {
        functions.put(key, func);
    }
}

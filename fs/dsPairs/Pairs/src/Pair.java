import java.util.Map;
import java.util.ArrayList;

public class Pair<K,V> implements Map.Entry<K,V> {
   K key;
   V value;

    public Pair(K key, V value) {
        this.key = key;
        this.value = value;
    }

    @Override
    public V setValue(V value) {
        V oldValue = this.value;
        this.value = value;

        return oldValue;
    }

    @Override
    public K getKey() {
        return this.key;
    }

    @Override
    public V getValue(){
        return this.value;
    }

    @Override
    public String toString(){
        return "(" + this.key + "," + this.value + ")";
    }

    @Override
    public boolean equals(Object o){
        if (o instanceof Pair){
            return this.key.equals(((Pair<?, ?>) o).getKey());
        }

        return false;
    }

    @Override
    public int hashCode(){
        return this.key.hashCode();
    }

    public static <K,V> Pair<V,K> swap(Pair<K,V> pair){
        K key = pair.getKey();
        V value = pair.getValue();
        return new Pair<>(value, key);
    }

    public static <K,V> Pair<K,V> of(K key, V value){
        return new Pair<>(key,value);
    }
    public static <T extends Comparable<T>> Pair<T, T> minmax(ArrayList<T> elements) {
        T max = elements.get(0);
        T min = elements.get(0);

        for (T i : elements) {
            if (i.compareTo(max) > 0) {
                max  = i;
            }
            else if (i.compareTo(min) < 0) {
                min = i;
            }
        }

        return new Pair<>(min, max);
    }
}

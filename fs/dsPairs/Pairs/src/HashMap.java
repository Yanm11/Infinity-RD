// approved by avshalom!
// 3/09/2024

import java.util.*;

public class HashMap<K, V> implements Map<K, V> {
    private List<List<Map.Entry<K,V>>> hashmap;
    private final int capacity;
    public static final int DEFAULT_INITIAL_CAPACITY = 16;

    private volatile int modCount = 0;

    private final SetOfEntries setOfEntries = new SetOfEntries();
    private final SetOfKeys setOfKeys = new SetOfKeys();
    private final CollectionOfValues collectionOfValues = new CollectionOfValues();

    public HashMap() {
        this(DEFAULT_INITIAL_CAPACITY);
    }

    public HashMap(int capacity) {
        this.capacity = capacity;
        hashmap = new ArrayList<>(capacity);

        for (int i = 0; i < capacity; ++i) {
            hashmap.add(new LinkedList<>());
        }
    }

    @Override
    public int size() {
        int size = 0;
        for (List<Map.Entry<K,V>> list : hashmap) {
            size += list.size();
        }

        return size;
    }

    @Override
    public boolean isEmpty() {
        for (List<Map.Entry<K,V>>list : hashmap) {
            if (!list.isEmpty()) {
                return false;
            }
        }

        return true;
    }

    // helper functions
    private int getIndexFromKey(Object key) {
        if (key == null) {
            return 0;
        }
        return key.hashCode() % capacity;
    }

    @Override
    public boolean containsKey(Object key) {
        int keyIndex = getIndexFromKey(key);

        for (Map.Entry<K,V> pair : hashmap.get(keyIndex)) {
            if (key == null ? pair.getKey() == null : pair.getKey().equals(key)) {
                return true;
            }
        }

        return false;

    }

    @Override
    public boolean containsValue(Object value) {
        for (List<Map.Entry<K,V>> list : hashmap) {
            for (Map.Entry<K,V> pair : list) {
                if (value == null ? pair.getValue() == null : pair.getValue().equals(value)) {
                    return true;
                }
            }
        }
        return false;
    }

    @Override
    public V get(Object key) {
        int keyIndex = getIndexFromKey(key);

        for (Map.Entry<K,V> pair : hashmap.get(keyIndex)) {
            if (key == null ? pair.getKey() == null : pair.getKey().equals(key)) {
                return pair.getValue();
            }
        }

        return null;
    }

    @Override
    public V put(K key, V value) {
        int keyIndex = getIndexFromKey(key);
        List<Map.Entry<K,V>> list = hashmap.get(keyIndex);

        for (Map.Entry<K,V> pair : list) {
            if (key == null ? pair.getKey() == null : pair.getKey().equals(key)) {
                return pair.setValue(value);
            }
        }

        list.add(new Pair<>(key, value));

        //increment modCount
        ++modCount;

        return null;
    }

    @Override
    public V remove(Object key) {
        int keyIndex = getIndexFromKey(key);
        List<Map.Entry<K,V>> list = hashmap.get(keyIndex);
        Iterator<Map.Entry<K,V>> iter = list.iterator();

        while (iter.hasNext()) {
            Map.Entry<K,V> pair = iter.next();
            if (key == null ? pair.getKey() == null : pair.getKey().equals(key)) {
                iter.remove();

                //increment modCount
                ++modCount;

                return pair.getValue();
            }
        }
        return null;
    }

    @Override
    public void putAll(Map<? extends K, ? extends V> m) {
        for (Entry<? extends K, ? extends V> entry : m.entrySet()) {
            this.put(entry.getKey(),entry.getValue());
        }
    }

    @Override
    public void clear() {
        for (List<Map.Entry<K,V> > list : hashmap) {
            list.clear();
        }
        //increment modCount
        ++modCount;
    }

    @Override //O(1) space
    public Set<K> keySet() {
        return setOfKeys;
    }

    @Override  //O(1) space
    public Collection<V> values() {
        return collectionOfValues;
    }

    @Override  //O(1) space
    public Set<Entry<K, V>> entrySet() {
        return setOfEntries;
    }

    private class SetOfEntries extends AbstractSet<Map.Entry<K, V>> {
        @Override
        public Iterator<Entry<K, V>> iterator() {
            return new EntriesIterator();
        }

        @Override
        public int size() {
            return HashMap.this.size();
        }

        private class EntriesIterator  implements Iterator<Map.Entry<K,V>> {
            private Iterator<List<Map.Entry<K,V>>> iterBuckets;
            private Iterator<Map.Entry<K,V>> iterList;
            private final int expectedModCount;

            private EntriesIterator() {
                iterBuckets = hashmap.iterator();
                iterList = iterBuckets.next().iterator();
                expectedModCount = modCount;
            }

            @Override
            public boolean hasNext() {
                // fast fail mechanism
                if (modCount != expectedModCount) {
                    throw new ConcurrentModificationException();
                }

                if (iterList.hasNext()){
                    return true;
                }

                while (iterBuckets.hasNext()) {
                    List<Map.Entry<K,V>> tmpList = iterBuckets.next();
                    if (!tmpList.isEmpty()) {
                        iterList = tmpList.iterator();

                        return true;
                    }
                }

                return false;
            }

            @Override
            public Map.Entry<K, V> next() {
                // fast fail mechanism
                if (modCount != expectedModCount) {
                    throw new ConcurrentModificationException();
                }
                //moves to the next available element
                hasNext();

                return iterList.next();
            }
        }
    }

    private class SetOfKeys extends AbstractSet<K> {
        @Override
        public Iterator<K> iterator() {
            return new KeysIterator();
        }

        @Override
        public int size() {
            return HashMap.this.size();
        }

        private class KeysIterator implements Iterator<K> {
            Iterator<Map.Entry<K,V>> iter = HashMap.this.entrySet().iterator();

            @Override
            public boolean hasNext() {
                return iter.hasNext();
            }

            @Override
            public K next() {
                return iter.next().getKey();
            }
        }
    }

    private class CollectionOfValues extends AbstractCollection<V> {

        @Override
        public Iterator<V> iterator() {
            return new ValueMapIterator();
        }

        @Override
        public int size() {
            return HashMap.this.size();
        }

        private class ValueMapIterator implements Iterator<V> {
            Iterator<Map.Entry<K,V>> iter = HashMap.this.entrySet().iterator();

            @Override
            public boolean hasNext() {
                return iter.hasNext();
            }

            @Override
            public V next() {
                return iter.next().getValue();
            }
        }
    }
}


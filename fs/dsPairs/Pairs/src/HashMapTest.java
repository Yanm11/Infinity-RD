import org.junit.*;
import org.junit.runners.MethodSorters;

import java.util.*;

        import static org.junit.Assert.*;
@FixMethodOrder(MethodSorters.NAME_ASCENDING)
public class HashMapTest {

    private static HashMap<String, String> hashString;
    private static HashMap<String, Integer> hashInteger;

    @BeforeClass
    public static void set(){
        hashString = new HashMap<>(32);
        hashInteger = new HashMap<>();
    }

    @Before
    public void clearMaps(){
        hashInteger.clear();
        hashString.clear();
    }

    @Test
    public void asize(){
        assertEquals(0, hashString.size());
        hashString.put("A", "String1");
        assertEquals(1, hashString.size());
        hashString.put("A", "String2");
        assertEquals(1, hashString.size());
        hashString.put("B", "String3");
        hashString.put("C", "String3");
        hashString.put("D", "String4");
        assertEquals(4, hashString.size());
        hashString.remove("A");
        hashString.remove("A");
        hashString.remove("B");
        hashString.remove("C");
        assertEquals(1, hashString.size());
        hashString.remove("D");
        assertEquals(0, hashString.size());
    }

    @Test
    public void bisEmpty(){
        assertTrue(hashString.isEmpty());
        hashString.put("A", "String1");
        assertFalse(hashString.isEmpty());
        hashString.put("B", "String1");
        hashString.remove("A");
        assertFalse(hashString.isEmpty());
        hashString.remove("B");
        assertTrue(hashString.isEmpty());
    }

    @Test
    public void containsKey(){
        assertTrue(hashString.isEmpty());
        assertFalse(hashString.containsKey("A"));
        hashString.put("A", "String1");
        assertTrue(hashString.containsKey("A"));
        hashString.put("B", "String3");
        hashString.put("C", "String3");
        hashString.put("D", "String4");
        assertTrue(hashString.containsKey("B"));
        assertTrue(hashString.containsKey("C"));
        assertTrue(hashString.containsKey("D"));
        assertFalse(hashString.containsKey("E"));
    }

    @Test
    public void containsValue(){
        assertTrue(hashInteger.isEmpty());
        assertFalse(hashInteger.containsValue("String1"));
        hashInteger.put("A", 2);
        assertTrue(hashInteger.containsValue(2));
        hashInteger.put("A", 3);
        assertFalse(hashInteger.containsValue(2));
        hashInteger.put("B", 3);
        hashInteger.put("C", 4);
        hashInteger.put("D", 5);
        assertTrue(hashInteger.containsValue(3));
        assertTrue(hashInteger.containsValue(4));
        assertTrue(hashInteger.containsValue(5));
    }

    @Test
    public void dget(){
        assertTrue(hashInteger.isEmpty());
        hashInteger.put("B", 3);
        hashInteger.put("C", 4);
        hashInteger.put("D", 5);
        assertEquals(Integer.valueOf(3), hashInteger.get("B"));
        assertEquals(Integer.valueOf(4), hashInteger.get("C"));
        assertEquals(Integer.valueOf(5), hashInteger.get("D"));
        assertEquals(null, hashInteger.get("S"));
    }

    @Test
    public void eput(){
        hashString.put("A", "STR1");
        assertEquals("STR1", hashString.get("A"));
        hashString.put("A", "STR2");
        assertEquals("STR2", hashString.get("A"));
        hashString.put("B", "STR3");
        assertEquals("STR3", hashString.get("B"));
        assertEquals("STR2", hashString.put("A", "STR4"));
        assertNull(hashString.put("E", "STR5"));
    }

    @Test
    public void fremove(){
        assertNull(hashString.remove("E"));
        hashString.put("A", "STR1");
        assertEquals("STR1", hashString.remove("A"));
        assertTrue(hashString.isEmpty());
        hashString.put("B", "STR2");
        assertEquals("STR2", hashString.remove("B"));
    }

    @Test
    public void gputAll(){
        HashMap<String, String> mapToAdd = new HashMap<>(100);
        mapToAdd.put("A", "STR1");
        mapToAdd.put("B", "STR2");
        mapToAdd.put("C", "STR4");
        hashString.put("A", "STR3");
        hashString.put("D", "STR5");
        hashString.putAll(mapToAdd);
        assertEquals(4, hashString.size());
        assertEquals("STR2", hashString.get("B"));
        assertEquals("STR1", hashString.get("A"));
        assertEquals("STR5", hashString.get("D"));
        assertEquals("STR4", hashString.get("C"));
    }

    @Test
    public void hclear(){
        HashMap<String, Integer> map = new HashMap<>(5);
        String[] keys = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N"};
        Integer[] values = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
        for(int i = 0; i < keys.length; ++i){
            map.put(keys[i], values[i]);
        }
        assertEquals(14, map.size());
        map.clear();
        assertTrue(map.isEmpty());
    }

    @Test
    public void jkeySet(){
        HashMap<String, Integer> map = new HashMap<>(5);
        String[] keys = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N"};
        Integer[] values = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
        for(int i = 0; i < keys.length; ++i){
            map.put(keys[i], values[i]);
        }

        Set<String> keySet = map.keySet();
        assertEquals(14, keySet.size());
        for (String key : keys) {
            assertTrue(keySet.contains(key));
        }

        System.out.println("Printing keySet:");
        for(String s : keySet){
            System.out.print(s + " ");
        }
        System.out.println();
    }

    @Test
    public void kvalues(){
        HashMap<String, Integer> map = new HashMap<>(5);
        String[] keys = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N"};
        Integer[] values = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
        for(int i = 0; i < keys.length; ++i){
            map.put(keys[i], values[i]);
        }

        Collection<Integer> collectionOfValues = map.values();
        assertEquals(14, collectionOfValues.size());
        ArrayList<Integer> intArray = new ArrayList<>(collectionOfValues);

        for (Integer val : intArray) {
            assertTrue(intArray.contains(val));
        }

        System.out.println("Printing values:");
        for(Integer val : intArray){
            System.out.print(val + " ");
        }
        System.out.println();
    }

    @Test
    public void isetEntry(){
        HashMap<String, Integer> map = new HashMap<>(5);
        String[] keys = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N"};
        Integer[] values = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
        for(int i = 0; i < keys.length; ++i){
            map.put(keys[i], values[i]);
        }

        Set<Map.Entry<String, Integer>> mapEntries = map.entrySet();
        assertEquals(14, mapEntries.size());

        for(Map.Entry<String, Integer> entry : mapEntries){
            assertTrue(mapEntries.contains(entry));
        }

        System.out.println("Printing entries:");
        for(Map.Entry<String, Integer> entry : map.entrySet()){
            System.out.println("Key: " + entry.getKey() + ", value: " + entry.getValue());
        }
    }

    @Test
    public void xfailFast(){
        Iterator<Map.Entry<String, String>> iterator = hashString.entrySet().iterator();
        hashString.put("a", "aaa");
        assertThrows(ConcurrentModificationException.class, iterator::hasNext);
    }

    @Test
    public void znullHandling(){
        HashMap<String, Integer> map = new HashMap<>(5);
        String[] keys = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N"};
        Integer[] values = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
        for(int i = 0; i < keys.length; ++i){
            map.put(keys[i], values[i]);
        }
        map.put(null, 4);
        assertTrue(map.containsKey(null));
        map.put(null, null);
        assertTrue(map.containsValue(null));
        assertEquals("test 1", null, map.get(null));
        assertEquals(15, map.size());
        Set<Map.Entry<String, Integer>> mapEntries = map.entrySet();
        Iterator<Map.Entry<String, Integer>> itertor = mapEntries.iterator();
        assertTrue(map.containsKey(null));
        Set<String> keySet = map.keySet();
        assertTrue(keySet.contains(null));
        Collection<Integer> valuesSet = map.values();
        assertTrue(valuesSet.contains(null));
        map.put("A", null);
        map.put("B", null);
        assertEquals(map.get("A"), map.get("B"));
        map.clear();
        assertEquals(0, map.size());
        assertTrue(map.isEmpty());
    }
}


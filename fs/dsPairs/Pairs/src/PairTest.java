import static org.junit.Assert.*;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

public class PairTest {
    Pair<String, Integer> pair1;
    Pair<String, Integer> pair2;
    Pair<Integer, String> pair3;
    Pair<String , Integer> pair4;
    ArrayList<Integer> elements;

    @Before
    public void setUp() {
        pair1 = new Pair<>("a", 2);
        pair2 = new Pair<>("b", 4);
        pair3 = new Pair<>(4, "b");
        pair4 = new Pair<>("a",5);
        elements = new ArrayList<>(Arrays.asList(1,2,3,4,5,6,7,8,9,2,3,0));
    }

    @Test
    public void setValue() {
        assertEquals((Integer) 2, pair1.setValue(5));
    }

    @org.junit.Test
    public void getKey() {
        assertEquals(pair1.getKey(), "a");
        assertEquals(pair2.getKey(),"b");
        assertEquals(pair3.getKey(),(Integer) 4);
    }

    @org.junit.Test
    public void getValue() {
        assertEquals(pair1.getValue(), (Integer) 2);
        assertEquals(pair2.getValue(),(Integer) 4);
        assertEquals(pair3.getValue(), "b");
        pair1.setValue(5);
        assertEquals(pair1.getValue(), (Integer) 5);
    }

    @org.junit.Test
    public void testToString() {
        assertEquals(pair1.toString(), "(a,2)");
    }

    @org.junit.Test
    public void testEquals() {
        assertNotEquals(pair1, pair2);
        assertEquals(pair1, pair4);
    }

    @org.junit.Test
    public void testHashCode() {
        assertEquals(pair4.hashCode(), pair1.hashCode());
        assertNotEquals(pair1.hashCode(), pair2.hashCode());
    }

    @org.junit.Test
    public void swap() {
        assertEquals(pair2,Pair.swap(pair3));
        assertEquals(pair3,Pair.swap(pair2));
    }

    @org.junit.Test
    public void of() {
        assertEquals(pair1,Pair.of(pair1.getKey(),pair1.getValue()));
    }

    @org.junit.Test
    public void minmax() {
        assertEquals(Collections.min(elements),Pair.minmax(elements).getKey());
        assertEquals(Collections.max(elements), Pair.minmax(elements).getValue());
    }
}
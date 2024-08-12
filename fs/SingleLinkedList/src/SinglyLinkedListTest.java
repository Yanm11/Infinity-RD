
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;

public class SinglyLinkedListTest {
    private SinglyLinkedList list;
    private int[] arr;

    @Before
    public void setUp() {
        list = new SinglyLinkedList();
        arr = new int[]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    }

    @Test
    public void testIsEmpty() {
        assertTrue("New list should be empty", list.isEmpty());

        list.pushFront(1);
        assertFalse("List with elements should not be empty", list.isEmpty());

        list.popFront();
        assertTrue("List should be empty after removing all elements", list.isEmpty());
    }

    @Test
    public void testPushFront() {
        for (int i = arr.length - 1; i >= 0; --i) {
            list.pushFront(arr[i]);
            assertEquals("Size should increase after pushFront", arr.length - i, list.size());
        }

        ListIterator iter = list.begin();
        for (int i = 0; i < arr.length; i++) {
            assertTrue("Iterator should have next", iter.hasNext());
            assertEquals("Elements should be in correct order", arr[i], iter.next());
        }
        assertFalse("Iterator should not have next after last element", iter.hasNext());
    }

    @Test
    public void testFind() {
        for (int value : arr) {
            list.pushFront(value);
        }

        ListIterator iter = list.find(arr[0]);
        assertNotNull("Should find existing element", iter);
        assertEquals("Found element should match", arr[0], iter.next());

        iter = list.find(20);
        assertNull("Should not find non-existing element", iter);
    }

    @Test
    public void testPopFront() {
        for (int value : arr) {
            list.pushFront(value);
        }

        for (int i = 0; i < arr.length; i++) {
            assertEquals("PopFront should return correct element", arr[arr.length - 1 - i], list.popFront());
            assertEquals("Size should decrease after popFront", arr.length - 1 - i, list.size());
        }

        assertTrue("List should be empty after popping all elements", list.isEmpty());
    }
}
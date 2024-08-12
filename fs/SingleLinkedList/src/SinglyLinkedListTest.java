
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import static org.junit.Assert.*;

public class SinglyLinkedListTest {
    SinglyLinkedList list;
    int[] arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int[] arrResult = {9, 8, 7, 6, 5, 4, 3, 2, 1};

    @BeforeClass
    public static void printBeforeClass() {
        System.out.println("Starting Tests...");
    }

    @Before
    public void setUp() {
        list = new SinglyLinkedList();
    }

    @AfterClass
    public static void printAfterClass() {
        System.out.println("\nFinished Tests successfully!");
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
        for (int i = 0; i < arr.length; ++i) {
            list.pushFront(arr[i]);

            assertEquals("Size should increase after pushFront", i + 1, list.size());
        }

        ListIterator iter = list.begin();
        for (int value: arrResult) {
            assertTrue("Iterator should have next", iter.hasNext());
            assertEquals("Elements should be in correct order", value, iter.next());
        }
        assertFalse("Iterator should not have next after last element", iter.hasNext());
    }

    @Test
    public void testFind() {
        for (int value : arr) {
            list.pushFront(value);
        }

        ListIterator iter = list.begin();

        for (int value : arrResult) {
            iter = list.find(value);

            assertNotNull("Should find existing element", iter);
            assertEquals("Found element should match", value, iter.next());
        }

        iter = list.find(20);
        assertNull("Should not find non-existing element", iter);
    }

    @Test
    public void testPopFront() {
        for (int value : arr) {
            list.pushFront(value);
        }

        int size = arr.length;

        for (int value : arrResult) {
            assertEquals("PopFront should return correct element", value, list.popFront());

            --size;

            assertEquals("Size should decrease after popFront", size, list.size());
        }

        assertTrue("List should be empty after popping all elements", list.isEmpty());
    }
}
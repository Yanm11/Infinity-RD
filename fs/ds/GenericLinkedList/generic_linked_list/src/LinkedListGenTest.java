
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import java.util.Iterator;
import java.util.ListIterator;

import static org.junit.Assert.*;

public class LinkedListGenTest {
    LinkedListGen<Integer> list1;
    LinkedListGen<Integer> list2;

    Integer[] arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Integer[] arr2 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    @Before
    public void setUp() {
        list1 = new LinkedListGen<>();
        list2 = new LinkedListGen<>();
    }

    @Test
    public void basicOperations() {
        // size
        assertEquals(list1.size(), 0);
        // is empty
        assertTrue(list1.isEmpty());
        // iterator
        Iterator<Integer> iter = list1.iterator();
        assertFalse(iter.hasNext());

        // push
        list1.pushFront(arr[0]);

        // size
        assertEquals(list1.size(), 1);
        // is empty
        assertFalse(list1.isEmpty());
        // iterator
        iter = list1.iterator();
        assertTrue(iter.hasNext());
        assertEquals(iter.next(), arr[0]);

        //pop
        assertEquals(list1.popFront(), arr[0]);

        // size
        assertEquals(list1.size(), 0);
        // is empty
        assertTrue(list1.isEmpty());
        // iterator
        iter = list1.iterator();
        assertFalse(iter.hasNext());
    }
    @Test
    public void printAllList() {
        for (Integer i : arr) {
            list1.pushFront(i);
        }
        for (Integer i : list1) {
            System.out.print(i + ", ");
        }
    }

    @Test
    public void pushFront() {
        for (Integer i : arr) {
            list1.pushFront(i);
            assertEquals(list1.size(), i.intValue());
        }

        Iterator<Integer> iter = list1.iterator();

        for (Integer i = arr[8]; i > 0; --i) {
            assertEquals(iter.next(), i);
        }

        assertThrows(NullPointerException.class, iter::next);
    }

    @Test
    public void popFront() {
        for (Integer i : arr) {
            list1.pushFront(i);
        }
        for (Integer i = arr[8]; i > 0; --i) {
            assertEquals(list1.popFront(), i);
        }

        assertThrows(EmptyListException.class, () -> list1.popFront());
    }

    @Test
    public void size() {
        assertEquals(list1.size(), 0);

        for (Integer i : arr) {
            list1.pushFront(i);
            assertEquals(list1.size(), i.intValue());
        }
        for (int i = 9; i > 0; --i) {
            assertEquals(i, list1.size());
            list1.popFront();
        }

        assertEquals(list1.size(), 0);
    }

    @Test
    public void isEmpty() {
        assertTrue(list1.isEmpty());
        list1.pushFront(arr[0]);
        assertFalse(list1.isEmpty());
        list1.popFront();
        assertTrue(list1.isEmpty());
    }

    @Test
    public void find() {
        for (Integer i : arr) {
            list1.pushFront(i);
        }
        Iterator<Integer> iter = list1.find(arr[0]);
        assertEquals(iter.next(), arr[0]);

        iter = list1.find(arr[8]);
        assertEquals(iter.next(), arr[8]);

        iter = list1.find(20);
        assertFalse(iter.hasNext());
    }

    @Test
    public void mergeLists() {
        for (Integer i : arr) {
            list1.pushFront(i);
        }
        for (Integer i : arr) {
            list2.pushFront(i);
        }

        int sizeOfNewList = list1.size() + list2.size();

        LinkedListGen<Integer> newlist = LinkedListGen.mergeLists(list1, list2);
        assertEquals(list1.size(), 0);
        assertEquals(list2.size(), 0);
        assertTrue(list1.isEmpty());
        assertTrue(list2.isEmpty());
        assertFalse(newlist.isEmpty());
        assertEquals(newlist.size(), sizeOfNewList);

        Iterator<Integer> iter = newlist.iterator();

        for (Integer i : arr2) {
            assertEquals(iter.next(), i);
        }
    }

    @Test
    public void printList() {
        for (Integer i : arr) {
            list1.pushFront(i);
        }

        LinkedListGen.printList(list1);
    }

    @Test
    public void newReverse() {
        for (Integer i : arr) {
            list1.pushFront(i);
        }
        LinkedListGen<Integer> newlist = LinkedListGen.newReverse(list1);

        for (Integer i : arr) {
            assertEquals(i, newlist.popFront());
        }
    }

    @Test
    public void iterator() {
        for (Integer i : arr) {
            list1.pushFront(i);
        }
        Iterator<Integer> iter = list1.iterator();
        assertTrue(iter.hasNext());
        assertEquals(iter.next(), arr[8]);
    }
}
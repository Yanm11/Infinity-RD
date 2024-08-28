// approved by ido

import java.util.ConcurrentModificationException;
import java.util.EmptyStackException;
import java.util.Iterator;

public class LinkedListGen<T> implements Iterable<T> {
    // private fields
    private Node<T> head = null;
    private Node<T> tail = null;
    private volatile int modCount = 0;

    // public functions
    public void pushFront(T t) {
        head = new Node<>(t, head);
        if (tail == null) {
            tail = head;
        }

        synchronized ("modCount") {
            ++modCount;
        }
    }
    // to do custom exception
    public T popFront() {
        T data;
        try {
            data = head.data;
            head = head.next;
        }
        catch (NullPointerException e) {
            throw new EmptyListException("Can not pop front from empty list", e);
        }

        //if list is empty again return tail to null
        if (isEmpty()) {
            tail = null;
        }

        synchronized ("modCount") {
            ++modCount;
        }

        return data;
    }

    public int size() {
        int count = 0;

        for (T data : this) {
            ++count;
        }

        return count;
    }

    public boolean isEmpty() {
        return head == null;
    }

    public Iterator<T> find(T data) {
        Iterator<T> iter = this.iterator();

        for (T listData : this) {
            if (listData.equals(data)) {
                return iter;
            }
            iter.next();
        }

        return (Iterator<T>) (new ListIterator<>(null));
    }

    //removes all nodes from both lists and returns a new one
    public static <T> LinkedListGen<T> mergeLists(LinkedListGen<T> list1, LinkedListGen<T> list2) {
        // undefined if same list - will return a looped list

        LinkedListGen<T> newList = new LinkedListGen<>();

        // assigning the head of list1 ad tail of list2 to the new list
        newList.head = list1.head;
        newList.tail = list2.tail;

        // assigning to the tail of list1 the head of list 2
        list1.tail.next = list2.head;

        // removing all the nodes from the old lists
        list1.head = null;
        list1.tail = null;
        list2.head = null;
        list2.tail = null;

        // increment modCount for list 1 and 2
        synchronized ("modCount update") {
            ++list1.modCount;
            ++list2.modCount;
        }

        return newList;
    }

    public static <T> void printList(LinkedListGen<T> list) {
      for (T data : list) {
            System.out.print(data + ", ");
        }
      System.out.println();
    }

    public static <T> LinkedListGen<T> newReverse(LinkedListGen<T> list) {
        LinkedListGen<T> newList = new LinkedListGen<>();

        for (T data : list) {
            newList.pushFront(data);
        }

        return newList;
    }

    @Override
    public Iterator<T> iterator() {
        return (Iterator<T>) new ListIterator<>(head);
    }

    // nested Node<T> class:
    private static class Node<E> {
        //private fields
        private E data;
        private Node<E> next;

        //constructor
        public Node(E data, Node<E> next) {
            this.data = data;
            this.next = next;
        }
    }


    // nested ListIterator<T> class:
    private class ListIterator<T> implements Iterator<T> {
        //private fields
        private Node<T> currNode;
        private final int expectedModCount;

        //constructor:
        public ListIterator(Node<T> node) {
            this.currNode = node;
            this.expectedModCount = modCount;
        }

        @Override
        public T next() {

            // fast fail mechanism
            if (modCount != expectedModCount) {
                throw new ConcurrentModificationException();
            }

            T data = currNode.data;
            currNode = currNode.next;

            return data;
        }

        @Override
        public boolean hasNext() {
            // fast fail mechanism
            if (modCount != expectedModCount) {
                throw new ConcurrentModificationException();
            }

            return currNode != null;
        }
    }

}

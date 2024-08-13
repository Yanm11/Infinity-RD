// yan meiri
// 11.8.2024
// approved by itai

public class SinglyLinkedList{
//    -------- private field(s) --------

    private Node head;

//    -------- public methods --------

    public SinglyLinkedList(){
        head = null;
    }

    public void pushFront(Object data){
        head = new Node(data, head);
    }

    public Object popFront(){
        Object data = head.data;
        head = head.next;

        return data;
    }

    public int size(){
        int listSize = 0;
        ListIterator iter = begin();

        while(iter.hasNext()){
            ++listSize;
            iter.next();
        }

        return listSize;
    }

    public boolean isEmpty(){
        return head == null;
    }

    public ListIterator begin(){
        return new ListIteratorIMP(head);
    }

    public ListIterator find(Object dataToMatch){
        ListIterator iterFirst = begin();
        ListIterator iterSecond = begin();

        while(iterFirst.hasNext()){
            if(dataToMatch.equals(iterFirst.next())){
                return iterSecond;
            }
            iterSecond.next();
        }

        return null;
    }

    //    -------- inner class Node --------
    private static class Node{
        private Object data;
        private Node next;

        public Node(Object data, Node next){
            this.data = data;
            this.next = next;
        }
    }

    //    -------- inner class LisIteratorIMP --------
    private static class ListIteratorIMP implements ListIterator{

        private Node node;

        public ListIteratorIMP(Node node){
            this.node = node;
        }

        @Override
        public boolean hasNext(){
            return node != null;
        }

        @Override
        public Object next(){
            Object data = node.data;
            node = node.next;

            return data;
        }
    }
}





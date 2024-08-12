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
        int list_size = 0;
        Node curr_node = head;

        while(curr_node != null){
            ++list_size;
            curr_node = curr_node.next;
        }

        return list_size;
    }

    public boolean isEmpty(){
        return head == null;
    }

    public ListIterator begin(){
        return new ListIteratorIMP(head);
    }

    public ListIterator find(Object dataToMatch){
        Node curr_node = head;

        while(curr_node != null){
            if(curr_node.data.equals(dataToMatch)){
                return new ListIteratorIMP(curr_node);
            }
            curr_node = curr_node.next;
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





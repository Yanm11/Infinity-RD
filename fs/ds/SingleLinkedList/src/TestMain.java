public class TestMain {
    public static void main(String[] args) {
        SinglyLinkedList list = new SinglyLinkedList();
        int[] arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int size = 0;

        //Test isEmpty1
        if (!list.isEmpty()){
            System.out.println("Failed test isEmpty1");
            return;
        }
        System.out.println("Passed test isEmpty1");

        // Test pushFront1
        for (int i = arr.length - 1; i >= 0; --i) {
            list.pushFront(arr[i]);
            ++size;

            if (size != list.size()) {
                System.out.println("Failed test pushFront1");
                return;
            }
        }
        System.out.println("Passed test pushFront1");

        //Test isEmpty2
        if (list.isEmpty()){
            System.out.println("Failed test isEmpty2");
            return;
        }
        System.out.println("Passed test isEmpty2");


        //Test pushFront2
        //Test next
        //Test hasNext
        ListIterator iter = list.begin();
        int data = 0;
        int i = 0;
        while (iter.hasNext()) {
            data = (int) iter.next();

            if (arr[i] != (data)) {
                System.out.println("Failed test pushFront2");
                return;
            }

            ++i;
        }
        if (i != list.size()) {
            System.out.println("Failed test hasNext");
            return;
        }

        System.out.println("Passed test pushFront2");
        System.out.println("Passed test next");
        System.out.println("Passed test hasNext");

        //Test find1
        iter = list.find(arr[0]);
        data = (int)iter.next();
        if (arr[0] != data) {
            System.out.println("Failed test find1");
            return;
        }
        System.out.println("Passed test find1");

        //Test find2
        iter = list.find(20);
        if (null != iter) {
            System.out.println("Failed test find2");
            return;
        }
        System.out.println("Passed test find2");

        // Test popFront
        int size2 = arr.length;

        for (i = arr.length - 1; i >= 0; --i) {
            data = (int)list.popFront();

            if (i != list.size() && data != arr[i]) {
                System.out.println("Failed test popFront");
                return;
            }
        }
        System.out.println("Passed test popFront");

        //Test isEmpty3
        if (!list.isEmpty()){
            System.out.println("Failed test isEmpty3");
            return;
        }
        System.out.println("Passed test isEmpty3");

        System.out.println("\nPassed ALL TESTS!!");
    }
}

import java.util.ArrayList;
import java.util.Arrays;

public class PrintArray {

    public static void main(String[] args) {
        //q1
        ArrayList<Integer> arrI = new ArrayList<>(Arrays.asList(1,2,3,4,5,6));
        ArrayList<String> arrS = new ArrayList<>(Arrays.asList("heloop","frfrf","rfwdqwq"));
        ArrayList<Float> arrF = new ArrayList<>(Arrays.asList(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f));

        PrintArray.printArray(arrI);
        PrintArray.printArray(arrS);
        PrintArray.printArray(arrF);

        //q2 + 3 + 4
        FooReference<Integer> foo = new FooReference<>(arrI);
        PrintArray.printArray(foo.arrGet());
        foo.arrSet(new ArrayList<>(Arrays.asList(9,8,7,6,5,4,3,2,1)));
        PrintArray.printArray(foo.arrGet());

        FooReference<String> foo2 = new FooReference<>(arrS);
        PrintArray.printArray(foo2.arrGet());
        foo2.arrSet(new ArrayList<>(Arrays.asList("world","Hello","!!!")));
        PrintArray.printArray(foo2.arrGet());

        System.out.println(foo.getClass());
        System.out.println(foo2.getClass());



    }

    public static <T> void printArray(ArrayList<T> arr) {
        for (T t : arr) {
            System.out.println(t);
        }
    }


}

class FooReference<T> {
    ArrayList<T> arr;

    public FooReference(ArrayList<T> arr) {
        this.arr = arr;
    }

    public ArrayList<T> arrGet() {
        return this.arr;
    }

    public void arrSet(ArrayList<T> arr) {
        this.arr = arr;
    }
}

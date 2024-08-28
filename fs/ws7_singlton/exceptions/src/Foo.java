import java.io.IOException;

public class Foo {
    public static void main(String[] args) {
        Foo foo = new Foo();
        byte[] arr = new byte[100];
        try {
            byte value = arr[100]; // This will throw an exception
            System.out.println(value);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Exception caught: " + e.getClass().getSimpleName());
            System.out.println("Exception message: " + e.getMessage());
        }
        // Calling func3
        try {
            foo.func3();
        } catch (MyException1 e) {
            System.out.println("Caught MyException1 from func3: " + e.getMessage());
        }

        // Calling func4
        try {
            foo.func4();
        } catch (MyException2 e) {
            System.out.println("Caught MyException2 from func4: " + e.getMessage());
        }

        HelperClass1 helper1 = new HelperClass1();
        helper1.doSomething();

        HelperClass2 helper2 = new HelperClass2();
        helper2.doSomethingElse();

    }

    public void func1() throws IOException {
        throw new IOException();
    }

    public void func2() {
        throw new NullPointerException();
    }
    public void func3() throws MyException1 {
        throw new MyException1("This is MyException1 from func3");
    }
    public void func4() throws MyException2 {
        throw new MyException2("This is MyException1 from func4");
    }
}




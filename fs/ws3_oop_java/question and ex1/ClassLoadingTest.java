class Parent {
    static {
        System.out.println("parent class static block 1");
    }
    {
        System.out.println("parent instance block 1");
    }
    public static int staticField1 = 9;

    public Parent() {
        System.out.println("parent constructor");
        System.out.println(staticField1);
        System.out.println(staticField2);
    }

    static {
        System.out.println("parent class static block 2");
    }
    {
        System.out.println("parents instance block 2");
    }
    public static void staticMethod() {
        System.out.println("parents's static method called");
    }

    public static int staticField2 = 8;
}

class Child extends Parent {
    static {
        System.out.println("Child class static block 1");
    }
    {
        System.out.println("Child instance block 1");
    }
    public static int staticField1 = 11;

    public Child() {
        System.out.println("Child constructor");
        System.out.println(staticField1);
        System.out.println(staticField2);
    }

    static {
        System.out.println("Child class static block 2");
    }
    {
        System.out.println("Child instance block 2");
    }
    public static void staticMethod() {
        System.out.println("Child's static method called");
    }

    public static int staticField2 = 10;
}

public class ClassLoadingTest {
    public static void main(String[] args) {
        System.out.println("1. Accessing Child's compile-time constant");
        System.out.println(Child.class.getName());

        System.out.println("\n4. Creating instance of Child");
        new Child();

        System.out.println("\n3. Accessing Child's static field");
        System.out.println(Child.staticField1);

        System.out.println("\n2. Calling Child's static method");
        Child.staticMethod();


        System.out.println("\n4. Creating instance of Child");
        new Child();
        new Parent();

    }
}
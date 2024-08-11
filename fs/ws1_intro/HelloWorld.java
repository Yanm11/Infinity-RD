public class HelloWorld {
    public static void main(String[] args) {
        // Call static method foo1 from MySecondClass
        MySecondClass.foo1();

        // Create an instance of MySecondClass to call the instance method foo2
        MySecondClass instance = new MySecondClass();
        instance.foo2();

        System.out.println("You are ga!!!");
    }
}


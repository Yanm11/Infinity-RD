public class Main {
    public static void main(String[] args) {
        OuterClass outerClass = new OuterClass();

        // Anonymous inner class to override bar() method
        OuterClass.InnerClass anonymousInnerClass = outerClass.new InnerClass() {
            @Override
            void bar() {
                int c = outerClass.plus(outerClass.x, outerClass.y) * 2; // Custom implementation, e.g., multiply the result by 2
                System.out.println("Anonymous Inner Class: c = " + c);
            }
        };

        anonymousInnerClass.bar(); // This will use the overridden method from the anonymous inner class
    }
}

class OuterClass {
    public int x = 1;
    public int y = 2;

    public int plus(int a, int b) {
        return a + b;
    }

    class InnerClass {
        void bar() {
            int c = plus(x, y);
            System.out.println("Original Inner Class: c = " + c);
        }
    }
}
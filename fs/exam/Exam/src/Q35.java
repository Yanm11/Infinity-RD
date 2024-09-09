public class Q35 {
}

class C {
    private String s = "123";

    class C1 {
        private C c = new C();
        private String str = "hello world";

        private void foo() {
            s = "456";
            System.out.println(str);
        }
    }

    class C2 {
        private C1 c1 = new C1();

        private void foo2() {
            c1.c.s = "abc";
        }
    }

    private static class C3 {
        private int i = 3;

        static void foo() {
            // Incorrect usage of "this" inside a static method
            // This will not compile
            // this.i = 5;
        }
    }

    void foo2() {
         String s1 = "hello";
    }
}

class Main {
    public static void main(String[] args) {
        C.C2 c2 = new C().new C2();
    }
}

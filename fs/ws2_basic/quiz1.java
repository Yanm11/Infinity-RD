class Point2D {
    private int x, y;

    public Point2D(int x, int y) {
            x = x;
    }
    public String toString() {
            return "[" + x + ", " + y + "]";
    }
    public static void foo(Integer i) { System.out.println("foo(Integer)");}
    public static void foo(short i) { System.out.println("foo(short)");}
    public static void foo(long i) { System.out.println("foo(long)");}
    public static void foo(int ... i) { System.out.println("foo(int ...)"); }

    public static void main (String []args) {
        System.out.println("questin 1");
        String s1 = "hi";
        String s2 = new String("hi");
        String s3 = "hi";
        if (s1.equals(s2)) {
            System.out.println("sl and s2 are equal");
        } else {
            System.out.println("sl and s2 are not equal");
        }
        if (s1 == s3) {
            System.out.println("sl and s3 are equal");
        } else {
            System.out.println("sl and s3 are not equal");
        }

        System.out.println("questin 2");
        Point2D point = new Point2D(10, 20);
        System.out.println(point);

        System.out.println("questin 3");
        Integer i = 10;
        Integer j = 11;
        Integer k = ++i; // INCR
        System.out.println("k == j is " + (k == i));
        System.out.println("k.equals(j) is " + k.equals(j));

        System.out.println("questin 4");
        int []arr1 = {1, 2, 3, 4, 5};
        int []arr2 = {1, 2, 3, 4, 5};
        System.out.println("arrl == arr2 is " + (arr1 == arr2));
        System.out.println("arrl.equals(arr2) is " + arr1.equals(arr2));

        System.out.println("questin 5");
        foo (10);
    }
}
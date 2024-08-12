public class Quiz2 {
    public static void main(String[] args) {
        //Question 1
        StringBuffer str = new StringBuffer("This, that, etc.!");
        System.out.println(str.replace(12,15,"etcetera"));

        //Question 2
        Boolean b = true;
        System.out.println(b ? true : false);

    }

    //Question 4
    class Point {
        private int x = 0, y;
        public Point (int X, int y) {
            this.x = x;
            this.y = y;
        }
        // DEFAULT_CTOR
        public Point () {
            this(0,0);
        }
    }

}

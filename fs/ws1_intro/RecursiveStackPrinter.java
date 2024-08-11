public class RecursiveStackPrinter {
    private static int counter = 0;

    public static void recursivePrint(int lim) {
        int frameNumber = ++counter;
        if (frameNumber > lim) {
            return;
        }
        System.out.printf("Frame %d\n", frameNumber);

        // Recursive call
        recursivePrint(lim);
    }

    public static void main(String[] args) {
        try {
            recursivePrint(10000);
        } catch (StackOverflowError e) {
            System.out.println("Stack overflow occurred after " + counter + " frames.");
        }
    }
}
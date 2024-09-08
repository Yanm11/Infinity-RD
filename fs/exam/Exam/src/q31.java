import java.io.FileNotFoundException;
import java.io.IOException;

public class q31 {
    public static void main(String[] args) {

    }
}

class Base {
    public static void foo() {}
    protected void bar(int num) {}
    private int lol(String s) { return 5; }
    public Object rofl(int num) throws IOException { return new Object(); }
}

class Derived extends Base {
    public static void foo() {}

    @Override
    protected void bar(int num) {}


    private int lol(String s) { return 3; }

    @Override
    public String rofl(int num) throws FileNotFoundException { return "hello"; }
}


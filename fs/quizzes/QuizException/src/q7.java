import java.io. IOException;
public class q7 {
    public static void main(String[] args) {

    }
}

class TestException1 {
    public void start() throws Exception {
    }

    public void foo() throws NullPointerException {
    }
}

class TestException2 extends TestException1 {
    public void start() throws IOException {
    }

    public void foo() throws RuntimeException {
    }
}

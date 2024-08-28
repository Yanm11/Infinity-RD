import java.io.IOException;

public class MyException2 extends IOException {
    public MyException2() {
        super();
    }

    public MyException2(String message) {
        super(message);
    }
}

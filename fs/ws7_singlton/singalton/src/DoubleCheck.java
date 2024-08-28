package il.co.ILRD.Singleton;

public class DoubleCheck {
    private static volatile DoubleCheck instance = null;

    private DoubleCheck(){}

    public static DoubleCheck getInstance() {
        if (instance == null) {
            synchronized (DoubleCheck.class) {
                if (instance == null) {
                    instance = new DoubleCheck();
                }
            }
        }
        return instance;
    }
}

package il.co.ILRD.Singleton;

public class EagerInitializationSingleton {
    private static final EagerInitializationSingleton instance = new EagerInitializationSingleton();

    private EagerInitializationSingleton() {}

    public static EagerInitializationSingleton getInstance() {
        return instance;
    }
}

public class Lazy {

    private static Lazy instance;

    private Lazy(){}

    public static Lazy getInstance(){
        if(null == instance){
            instance = new Lazy();
        }
        return instance;
    }
}

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

public class HolderIdiom{

    private HolderIdiom(){};

    public static class LazyHolder {
        private static final HolderIdiom INSTANCE = new HolderIdiom();
    }

    public static HolderIdiom getInstance(){
        return LazyHolder.INSTANCE;
    }

}

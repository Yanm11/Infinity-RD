package il.co.ILRD.Singleton;

public class HolderIdiom{

    private HolderIdiom(){};

    public static class LazyHolder {
        private static final HolderIdiom INSTANCE = new HolderIdiom();
    }

    public static HolderIdiom getInstance(){
        return LazyHolder.INSTANCE;
    }

}

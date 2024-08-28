package il.co.ILRD.Singleton;

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
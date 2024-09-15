import sun.rmi.server.Dispatcher;

import java.util.function.Consumer;

abstract public class Subscriber<T> {
    //private fields

    public void register(Publisher publisher){}

    public void unRegister(){}

    public T getData(){}

}

abstract class Publisher {
    //private fields

    public <T> void register(Subscriber<T> subscriber){}

    public void produce(T data) {}

    public void close(){}
}

class CallBack<T> {
    //private fields

    //ctor
    public CallBack(Consumer<T> consumer){}

    public void unRegister(){}

    public void update(T data){}

    public void stopUpdate(){}

    public void setDecpatcher(Dispatcher<T> dispatcher){}

}

class Dispatcher<T> {

}


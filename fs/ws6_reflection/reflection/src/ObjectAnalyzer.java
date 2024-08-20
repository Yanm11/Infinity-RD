import java.lang.reflect.*;
import java.util.Arrays;

public class ObjectAnalyzer {

    public static void main(String[] args) {
        analyzeClass(Foo.class);
    }

    public static void analyzeClass(Class<?> clazz) {
        System.out.println("Analyzing class: " + clazz.getName());

        // Print the ancestor of class Foo
        Class<?> superClass = clazz.getSuperclass();
        System.out.println("Ancestor: " + (superClass.getName() ));

        // List the modifiers and implemented interfaces of Foo
        int modifiers = clazz.getModifiers();
        System.out.println("Modifiers: " + Modifier.toString(modifiers));
        Class<?>[] interfaces = clazz.getInterfaces();
        System.out.println("Implemented interfaces: " + Arrays.toString(interfaces));

        // List the members of class Foo
        System.out.println("\nMembers of class " + clazz.getSimpleName() + ":");
        listMembers(clazz);

        // Create a new Foo instance
        Object instance = createInstance(clazz);

        // Call instance method Foo.f1()
        if (instance != null) {
            callMethod(instance, "f1");
        }
    }

    private static void listMembers(Class<?> clazz) {
        System.out.println("Fields:");
        for (Field field : clazz.getDeclaredFields()) {
            System.out.println("  " + field.toString());
        }

        System.out.println("Constructors:");
        for (Constructor<?> constructor : clazz.getDeclaredConstructors()) {
            System.out.println("  " + constructor.toString());
        }

        System.out.println("Methods:");
        for (Method method : clazz.getDeclaredMethods()) {
            System.out.println("  " + method.toString());
        }
    }

    private static Object createInstance(Class<?> clazz) {
        try {
            Constructor<?> constructor = clazz.getDeclaredConstructor();
            Object instance = constructor.newInstance();
            System.out.println("\nCreated new instance of " + clazz.getSimpleName());
            return instance;
        } catch (NoSuchMethodException | InstantiationException | IllegalAccessException | InvocationTargetException e) {
            System.out.println("Error creating instance: " + e.getMessage());
            return null;
        }
    }

    private static void callMethod(Object instance, String methodName) {
        try {
            Method method = instance.getClass().getDeclaredMethod(methodName);
            method.setAccessible(true);
            System.out.println("\nCalling method " + methodName + "()");
            method.invoke(instance);
        } catch (NoSuchMethodException | IllegalAccessException | InvocationTargetException e) {
            System.out.println("Error calling method: " + e.getMessage());
        }
    }
}

// Example Foo class for demonstration
final class Foo implements Runnable {
    private int x;
    public String y;

    public Foo() {
        this.x = 10;
        this.y = "Hello";
    }

    private void f1() {
        System.out.println("Method f1 called");
    }

    public void run() {
        System.out.println("Running");
    }
}
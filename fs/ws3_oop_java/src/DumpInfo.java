import java.lang.reflect.*;

public class DumpInfo {
    public static void main(String[] args) {

        String className = args[0];

        try {
            Class<?> cls = Class.forName(className);
            dumpClassInfo(cls);
        } catch (ClassNotFoundException e) {
            System.out.println("Class not found: " + className);
        }
    }

    private static void dumpClassInfo(Class<?> cls) {
        System.out.println("Class Information for: " + cls.getName());
        System.out.println("------------------------------------");

        // Superclass
        System.out.println("Superclass: " + (cls.getSuperclass() != null ? cls.getSuperclass().getName() : "None"));

        // Interfaces
        Class<?>[] interfaces = cls.getInterfaces();
        System.out.println("\nInterfaces:");
        for (Class<?> intf : interfaces) {
            System.out.println("  " + intf.getName());
        }

        // Constructors
        System.out.println("\nConstructors:");
        for (Constructor<?> constructor : cls.getDeclaredConstructors()) {
            System.out.println("  " + constructor);
        }

        // Fields
        System.out.println("\nFields:");
        for (Field field : cls.getDeclaredFields()) {
            System.out.println("  " + Modifier.toString(field.getModifiers()) + " " + field.getType().getSimpleName() + " " + field.getName());
        }

        // Methods
        System.out.println("\nMethods:");
        for (Method method : cls.getDeclaredMethods()) {
            System.out.println("  " + method);
        }
    }
}
import java.util.HashMap;

public class Q36 {
}

class Calculator {
    HashMap<String,Operator> mapOperator = new HashMap<>();

    public Calculator() {
        // constructor code if needed

        Operator subtraction = new Operator() {
            public int operate(int a, int b) {
                return a - b;
            }
        };

        class Devision implements Calculator.Operator {
            public int operate(int a, int b) {
                return a / b;
            }
        }

        addOperator("addition",(a, b) -> a + b);
        addOperator("subtraction", subtraction);
        addOperator("multiplication", new Multiplacation());
        addOperator("division", new Devision());
    }

    interface Operator {
        int operate(int a, int b);
    }

    public class Multiplacation implements Operator{
        @Override
        public int operate(int a, int b) {
                return a * b;
            }
    }

    public void addOperator(String key, Operator o) {
        mapOperator.put(key, o);
    }

    public int operate(String key, int a, int b) {
        return mapOperator.get(key).operate(a, b);
    }

    public static void main(String[] args) {
        Calculator calc = new Calculator();
        int sum = calc.operate("addition", 3, 4);
        int sub = calc.operate("subtraction", 4, 3);
        int mul = calc.operate("multiplication", 3, 4);
        int dev = calc.operate("division", 8, 2);

        System.out.println(sum);

        System.out.println(sub);

        System.out.println(mul);

        System.out.println(dev);
    }
}



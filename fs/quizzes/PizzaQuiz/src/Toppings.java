public abstract class Toppings implements Pizza {
    private Pizza pizza;

    public Toppings(Pizza pizza) {
        this.pizza = pizza;
    }

    @Override
    public String getDescription() {
        return pizza.getDescription();
    }

    @Override
    public int getPrice() {
        return pizza.getPrice();
    }
}

class FreshTomato extends Toppings {
    private String name = "with Fresh Tomato ";
    private int price = 1;

    public FreshTomato(Pizza pizza) {
        super(pizza);
    }

    @Override
    public String getDescription() {
        return super.getDescription() + name;
    }

    @Override
    public int getPrice() {
        return super.getPrice() + price;
    }
}

class BBQ extends Toppings {
    private String name = "with BBQ ";
    private int price = 5;

    public BBQ(Pizza pizza) {
        super(pizza);
    }

    @Override
    public String getDescription() {
        return super.getDescription() + name;
    }

    @Override
    public int getPrice() {
        return super.getPrice() + price;
    }
}

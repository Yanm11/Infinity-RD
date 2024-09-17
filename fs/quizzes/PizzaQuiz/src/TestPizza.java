public class TestPizza {
    public static void main(String[] args) {
        Pizza myPizza = new PeppyPaneer();
        System.out.println("the price of " + myPizza.getDescription() + "is " + myPizza.getPrice());

        myPizza = new FreshTomato(myPizza);
        System.out.println("the price of " + myPizza.getDescription() + "is " + myPizza.getPrice());

        myPizza = new FreshTomato(myPizza);
        System.out.println("the price of " + myPizza.getDescription() + "is " + myPizza.getPrice());

        myPizza = new BBQ(myPizza);
        System.out.println("the price of " + myPizza.getDescription() + "is " + myPizza.getPrice());
    }
}

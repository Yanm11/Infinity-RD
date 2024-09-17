public class PeppyPaneer implements Pizza{
    private String name = "Peppy Paneer Pizza ";
    private int price = 10;

    @Override
    public String getDescription() {
        return name;
    }

    @Override
    public int getPrice() {
        return price;
    }
}

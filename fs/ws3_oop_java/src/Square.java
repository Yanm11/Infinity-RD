import java.awt.*;

public class Square extends Rectangle {

    //constructors
    public Square() {
        super();
    }
    public Square(double side) {
        super(side, side);
    }
    public Square(double side, String color, boolean filled) {
        super(side, side, color, filled);
    }

    // setters and getters
    public double getSide(){
        return getWidth();
    }
    public void setSide(double side){
        setWidth(side);
    }

    @Override
    public void setWidth(double side){
        setWidth(side);
        setLength(side);
    }

    @Override
    public void setLength(double side){
        setLength(side);
        setWidth(side);
    }

    @Override
    public String toString() {
        return "A Square with side: " + getSide() + "which is a subclass of " + super.toString();
    }
}
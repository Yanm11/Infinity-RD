package il.co.ilrd.Factory.src;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class FactoryTest {

    // Static method for creating Square
    public static Square createSquare(Double side) {
        return new Square(side);
    }

    // Instance method for creating a custom Circle
    public Circle createCustomCircle(Double radius) {
        return new Circle(radius);
    }

    //creating a factory of shapes
    Factory<String, Shape, Double> shapeFactory = new Factory<>();

    @Test
    public void addAndCreate() {

        // Lambda function for Circle creation
        shapeFactory.add("CIRCLE", radius -> new Circle(radius));

        // Static method reference for Square creation
        shapeFactory.add("SQUARE", FactoryTest::createSquare);

        // Instance method reference for creating a customizable object
        FactoryTest customFactory = new FactoryTest();
        shapeFactory.add("CUSTOM_CIRCLE", customFactory::createCustomCircle);

        // Creating shapes
        Shape circle = shapeFactory.create("CIRCLE", 5.0);
        circle.draw();  // Output: Drawing a circle with radius: 5.0

        Shape square = shapeFactory.create("SQUARE", 4.0);
        square.draw();  // Output: Drawing a square with side: 4.0

        Shape customCircle = shapeFactory.create("CUSTOM_CIRCLE", 7.0);
        customCircle.draw();  // Output: Drawing a custom circle with radius: 7.0
    }

}


// Circle Class
class Circle implements Shape {
    private double radius;

    public Circle(double radius) {
        this.radius = radius;
    }

    @Override
    public void draw() {
        System.out.println("Drawing a circle with radius: " + radius);
    }
}

// Square Class
class Square implements Shape {
    private double side;

    public Square(double side) {
        this.side = side;
    }

    @Override
    public void draw() {
        System.out.println("Drawing a square with side: " + side);
    }
}

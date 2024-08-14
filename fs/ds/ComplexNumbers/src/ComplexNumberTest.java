import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

public class ComplexNumberTest {
    ComplexNumber num;
    ComplexNumber num2;

    @Before
    public void setUp() {
        num = new ComplexNumber(1,2);
        num2 = new ComplexNumber(3,1);
    }

    @Test
    public void getReal() {
        assertEquals(1,num.getReal(), 0);
    }

    @Test
    public void setReal() {
        num.setReal(3);
        assertEquals(3,num.getReal(), 0);
    }

    @Test
    public void getImaginary() {
        assertEquals(2,num.getImaginary(),0);
    }

    @Test
    public void setImaginary() {
        num.setImaginary(4);
        assertEquals(4,num.getImaginary(),0);
    }

    @Test
    public void setValue() {
        num.setValue(4,5);
        assertEquals(5,num.getImaginary(),0);
        assertEquals(4,num.getReal(),0);
    }

    @Test
    public void isReal() {
        assertFalse(num.isReal());

        num.setImaginary(0);
        assertTrue(num.isReal());

        num.setValue(0,0);
        assertTrue(num.isReal());
    }

    @Test
    public void isImaginary() {
        assertTrue(num.isImaginary());
        num.setImaginary(0);
        assertFalse(num.isImaginary());

        num.setValue(0,0);
        assertFalse(num.isImaginary());
    }

    @Test
    public void add() {
        ComplexNumber addNum = num.add(num2);
        assertEquals(4,addNum.getReal(),0);
        assertEquals(3,addNum.getImaginary(),0);
    }

    @Test
    public void subtract() {
        ComplexNumber subNum = num.subtract(num2);
        assertEquals(-2,subNum.getReal(),0);
        assertEquals(1,subNum.getImaginary(),0);
    }

    @Test
    public void multipleWith() {
        ComplexNumber muliNum = num.multipleWith(num2);
        assertEquals(1,muliNum.getReal(),0);
        assertEquals(7,muliNum.getImaginary(),0);

        num.setValue(-3,-8);

        muliNum = num.multipleWith(num2);
        assertEquals(-1,muliNum.getReal(),0);
        assertEquals(-27,muliNum.getImaginary(),0);
    }

    @Test
    public void divideBy() {
        ComplexNumber divNum = num.divideBy(num2);
        assertEquals((double) 5 /10,divNum.getReal(),0);
        assertEquals((double) 5 /10,divNum.getImaginary(),0);

        num.setValue(-3,-8);

        divNum = num.divideBy(num2);
        assertEquals((double) -17 / 10,divNum.getReal(),0);
        assertEquals((double) -21 /10,divNum.getImaginary(),0);
    }

    @Test
    public void parse() {
        ComplexNumber parseNum = ComplexNumber.parse("1+2i");
        assertEquals(1,parseNum.getReal(),0);
        assertEquals(2,parseNum.getImaginary(),0);

        num.setValue(-3,-8);
        parseNum = ComplexNumber.parse("-3   + -8i");
        assertEquals(-3,parseNum.getReal(),0);
        assertEquals(-8,parseNum.getImaginary(),0);

        num.setValue(3,-5);
        parseNum = ComplexNumber.parse("3 + -5i");
        assertEquals(3,parseNum.getReal(),0);
        assertEquals(-5,parseNum.getImaginary(),0);

        num.setValue(-6,7);
        parseNum = ComplexNumber.parse(num.toString());
        assertEquals(-6,parseNum.getReal(),0);
        assertEquals(7,parseNum.getImaginary(),0);
    }

    @Test
    public void testEquals() {
        assertFalse(num.equals(num2));
        num.setValue(num2.getReal() ,num2.getImaginary());
        assertTrue(num.equals(num2));
        num.setReal(8);
        assertFalse(num.equals(num2));
        num.setValue(num2.getReal() ,0);
        assertFalse(num.equals(num2));
    }

    @Test
    public void testHashCode() {
        assertNotEquals(num.hashCode(),num2.hashCode());
        num.setValue(num2.getReal() ,num2.getImaginary());
        assertEquals(num.hashCode(),num2.hashCode());
    }

    @Test
    public void compareTo() {
        assertTrue(num.compareTo(num2) < 0);
        num.setValue(-3,-8);
        assertTrue(num.compareTo(num2) > 0);
        num.setValue(num2.getReal() ,num2.getImaginary());
        assertEquals(0, num.compareTo(num2));
    }

    @Test
    public void testToString() {
        String toStringNum = "1.0 + 2.0i";
        assertEquals(toStringNum,num.toString());
        String toStringNum2 = "3.0 + 1.0i";
        assertEquals(toStringNum2,num2.toString());
        toStringNum = "-3.0 + -8.0i";
        num.setValue(-3,-8);
        assertEquals(toStringNum,num.toString());
    }
}
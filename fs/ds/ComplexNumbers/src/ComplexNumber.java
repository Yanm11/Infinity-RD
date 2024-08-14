// yan meiri
// 14.8.2024
// approved by hadad

import java.util.Objects;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ComplexNumber implements Comparable<ComplexNumber> {

    private double real;
    private double imaginary;

    // Constructors
    public ComplexNumber(){
        this(0,0);
    }

    public ComplexNumber(double real, double imaginary){
        this.real = real;
        this.imaginary = imaginary;
    }

    // Getters and setters
    public double getReal() {
        return real;
    }

    public void setReal(double real) {
        this.real = real;
    }

    public double getImaginary() {
        return imaginary;
    }

    public void setImaginary(double imaginary) {
        this.imaginary = imaginary;
    }

    // Set the complex number
    public void setValue(double real, double imaginary){
        this.setReal(real);
        this.setImaginary(imaginary);
    }

    // Check if the object is real
    public boolean isReal(){
        return ((Double)(this.getImaginary())).equals(0.0);
    }

    // Check if the object is imaginary
    public boolean isImaginary(){
        return !this.isReal();
    } // if real and imaginary is 0 its type is real

    // Add between 2 complex numbers
    public ComplexNumber add(ComplexNumber complexNumber){
        double newReal = this.getReal() + complexNumber.getReal();
        double newImaginary = this.getImaginary() + complexNumber.getImaginary();

        return new ComplexNumber(newReal, newImaginary);
    }

    // Subtract between 2 complex numbers
    public ComplexNumber subtract(ComplexNumber complexNumber){
        double newReal = this.getReal() - complexNumber.getReal();
        double newImaginary = this.getImaginary() - complexNumber.getImaginary();

        return new ComplexNumber(newReal, newImaginary);
    }

    // Multiply two complex number
    public ComplexNumber multipleWith(ComplexNumber complexNumber){
        double newReal = (this.getReal() * complexNumber.getReal() -
                          this.getImaginary() * complexNumber.getImaginary());
        double newImaginary = (this.getReal() * complexNumber.getImaginary() +
                               this.getImaginary() * complexNumber.getReal());

        return new ComplexNumber(newReal, newImaginary);
    }

    // Divide two complex number - if divide by 0 is undefined
    public ComplexNumber divideBy(ComplexNumber complexNumber){
        double divisor = complexNumber.pow2Self();

        double newReal = ((this.getReal() * complexNumber.getReal() +
                           this.getImaginary() * complexNumber.getImaginary()) / divisor);

        double newImaginary = ((this.getImaginary() * complexNumber.getReal() -
                                this.getReal() * complexNumber.getImaginary()) / divisor);

        return new ComplexNumber(newReal, newImaginary);
    }

    // Parse string to complex number. pattern: x + yi
    public static ComplexNumber parse(String expression) {
        // Regex pattern to match the complex number format "x + yi"
        String regex = "([+-]?\\d*\\.?\\d+)\\s*\\+\\s*([+-]?\\d*\\.?\\d+)i";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(expression);

        if (matcher.matches()) {
            // Group 1 is the value of real, Group 2 is the value of imaginary
            double newReal = Double.parseDouble(matcher.group(1));
            double newImaginary = Double.parseDouble(matcher.group(2));

            return new ComplexNumber(newReal, newImaginary);
        }
        else {
            return null;
        }
    }

    // Override equals to compare between 2 complex numbers
    @Override
    public boolean equals(Object o) {

        if (o instanceof ComplexNumber) {
            ComplexNumber other = (ComplexNumber) o;

            Double otherReal = other.getReal();
            Double otherImaginary = other.getImaginary();
            Double thisReal = this.getReal();
            Double thisImaginary = this.getImaginary();

            return thisReal.equals(otherReal) && thisImaginary.equals(otherImaginary);
        }
        return false;
    }

    // Override hashCode to comply with our new equals implementation
    @Override
    public int hashCode() {
        return Objects.hash(this.getReal(), this.getImaginary());
    }

    @Override
    public int compareTo(ComplexNumber num){
        double absThis = Math.sqrt(this.pow2Self());
        double absNum = Math.sqrt(num.pow2Self());

        return Double.compare(absThis, absNum);
    }

    @Override
    public String toString() {
        return  real + " + " + imaginary + "i";
    }

    // Helper functions
    private double pow2Self(){
        return (Math.pow(this.getReal(), 2) + Math.pow(this.getImaginary(), 2));
    }
}

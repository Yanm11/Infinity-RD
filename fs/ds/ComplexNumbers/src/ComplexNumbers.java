public class ComplexNumbers {
    // ----- fields -------
    private double real;
    private double imaginary;

    // ----- ctor -----
    public ComplexNumbers(){
        real = 0.0;
        imaginary = 0.0;

    }
    public ComplexNumbers(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;

    }

    // ---- getters methods -----
    public double getReal() {
        return real;
    }
    public double getImaginary() {
        return imaginary;
    }
    // ------ setters methods -----
    public void setReal(double real) {
        this.real = real;
    }
    public void setImaginary(double imaginary) {
        this.imaginary = imaginary;
    }
    public setValue(double real, double imaginary){
        setReal(real);
        setImaginary(imaginary);
    }

    // ----- boolean methods ------
    boolean isReal(){
    }
    boolean isImaginary(){
    }

    //---- override method ----
    @Override
    public


}

package lab1;

public class ComplexNumber {
    private Double real;
    private Double imag;

    public ComplexNumber(Double real, Double imag) {
        this.real = real;
        this.imag = imag;
    }

    public Double getReal() {
        return real;
    }

    public void setReal(Double real) {
        this.real = real;
    }

    public Double getImag() {
        return imag;
    }

    public void setImag(Double imag) {
        this.imag = imag;
    }

    public ComplexNumber getConjugate() {
        return new ComplexNumber(real, -imag);
    }

    public Double distanceTo(ComplexNumber target) {
        Double realPow2 = Math.pow(target.real - this.real, 2);
        Double imagPow2 = Math.pow(target.imag - this.imag, 2);
        return Math.sqrt(realPow2 + imagPow2);
    }

    @Override
    public String toString() {
        return real.toString() + (imag < 0 ? "" : "+") + imag.toString() + "i";
    }

    public static ComplexNumber fromString(String s) {
        String input = s.replace("+", " +").replace("-", " -").trim();
        String[] numbers = input.split(" ");
        if (numbers.length > 2) {
            return null;
        }

        Double real = null;
        Double imag = null;
        for (String n : numbers) {
            if (n.endsWith("i")) {
                if (imag != null) return null;
                imag = Double.parseDouble(n.replace("i", ""));
            } else {
                if (real != null) return null;
                real = Double.parseDouble(n);
            }
        }

        real = real == null ? 0 : real;
        imag = imag == null ? 0 : imag;
        return new ComplexNumber(real, imag);
    }
}

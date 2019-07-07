package lab1;

import java.util.Arrays;

public class ComplexNumberOperation {
    private ComplexNumber a;
    private ComplexNumber b;
    private Operation operation;

    public ComplexNumberOperation(ComplexNumber a, ComplexNumber b, Operation operation) {
        this.a = a;
        this.b = b;
        this.operation = operation;
    }

    public ComplexNumber doOperation() {
        switch (operation) {
            case ADD:
                return new ComplexNumber(
                        a.getReal() + b.getReal(),
                        a.getImag() + b.getImag()
                );
            case SUB:
                return new ComplexNumber(
                        a.getReal() - b.getReal(),
                        a.getImag() - b.getImag()
                );
            case MUL:
                return new ComplexNumber(
                        a.getReal() * b.getReal() - a.getImag() * b.getImag(),
                        a.getReal() * b.getImag() + a.getImag() * b.getReal()
                );
            case DIV:
                ComplexNumber numerator = new ComplexNumberOperation(a, b.getConjugate(), Operation.MUL).doOperation();
                ComplexNumber denominator = new ComplexNumberOperation(b, b.getConjugate(), Operation.MUL).doOperation();
                return new ComplexNumber(
                        numerator.getReal() / denominator.getReal(),
                        numerator.getImag() / denominator.getReal()
                );
            default:
                throw new IllegalStateException("Why is this happening?");
        }
    }
}

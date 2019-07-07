package lab1;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

public class Main {
    static Boolean areArgsValidExpression(String[] args) {
        if (args.length % 2 == 0) return false;
        for (Integer i = 0; i < args.length; ++i) {
            if (i % 2 == 0) {
                return ComplexNumber.fromString(args[i]) != null;
            } else {
                return Operation.fromRepr(args[i]) != null;
            }
        }
        return true;
    }

    static ComplexNumber computeArgsExpression(String[] args) {
        ComplexNumber a = ComplexNumber.fromString(args[0]);
        for (Integer i = 1; i < args.length; i += 2) {
            ComplexNumber b = ComplexNumber.fromString(args[i + 1]);
            ComplexNumberOperation op = new ComplexNumberOperation(a, b, Operation.fromRepr(args[i]));
            a = op.doOperation();
        }
        return a;
    }

    public static void main(String[] args) {
        System.out.println(areArgsValidExpression(args));
        if (areArgsValidExpression(args)) {
            ComplexNumber result = computeArgsExpression(args);
            System.out.println(result);

            List<String> argsCopy = new ArrayList<>(Arrays.asList(args));
            argsCopy.removeIf(s -> Operation.fromRepr(s) != null);
            List<ComplexNumber> points = argsCopy.stream()
                    .map(s -> ComplexNumber.fromString(s))
                    .collect(Collectors.toList());

            Polygon polygon = new Polygon(points.toArray(new ComplexNumber[points.size()]));
            System.out.println(polygon.computePerimeter());
        }
    }
}

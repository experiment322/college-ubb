package lab1;

import java.util.List;

import lab1.ComplexNumber;

public class Polygon {
    private ComplexNumber[] points;

    public Polygon(ComplexNumber... points) {
        this.points = points;
    }

    public Double computePerimeter() {
        if (points == null || points.length < 2) return 0.0;
        Double perimeter = 0.0;
        for (Integer i = 0; i < points.length - 1; ++i) {
            perimeter += points[i].distanceTo(points[i + 1]);
        }
        return perimeter;
    }
}

package utils;

import java.math.BigInteger;

public class NumberUtils {
    public static Integer tryParseInteger(String s) {
        try {
            return new Integer(s);
        } catch (Exception e) {
            return null;
        }
    }

    public static Double tryParseDouble(String s) {
        try {
            return new Double(s);
        } catch (Exception e) {
            return null;
        }
    }

    public static BigInteger tryParseBigInteger(String s) {
        try {
            return new BigInteger(s);
        } catch (Exception e) {
            return null;
        }
    }
}

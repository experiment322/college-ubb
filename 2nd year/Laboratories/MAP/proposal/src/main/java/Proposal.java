class Test {
    static void print(Object object) {
        System.out.println("object");
    }

    static void print(String string) {
        System.out.println("string");
    }
}

public class Proposal {
    public static void main(String[] args) {
        execute(null);
    }

    static void execute(Test test) {
        test.print(null);
    }
}

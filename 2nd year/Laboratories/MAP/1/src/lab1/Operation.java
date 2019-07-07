package lab1;

public enum Operation {
    ADD("+"), SUB("-"), MUL("*"), DIV("/");

    private String repr;

    private Operation(String repr) {
        this.repr = repr;
    }

    public static Operation fromRepr(String repr) {
        for (Operation op : Operation.values()) {
            if (op.repr.equals(repr)) return op;
        }
        return null;
    }
}

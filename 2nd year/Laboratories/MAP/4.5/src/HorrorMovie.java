public class HorrorMovie extends Movie {
    private Integer priority;

    public HorrorMovie(Integer id, String name, Integer year, Double rating, Integer priority) {
        super(id, name, year, rating);
        this.priority = priority;
    }

    public Integer getPriority() {
        return priority;
    }

    public void setPriority(Integer priority) {
        this.priority = priority;
    }

    @Override
    public String toString() {
        return "HorrorMovie{" +
                "priority=" + priority +
                "} " + super.toString();
    }
}

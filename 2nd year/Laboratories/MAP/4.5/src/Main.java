import java.util.ArrayList;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        List<Movie> movies = new ArrayList<>();
        movies.add(new Movie(1, "Chuck Norris: Chuck Norris", 2020, 1.0 / 0.0));
        movies.add(new Movie(2, "The Party", 2005, 3.0));
        movies.add(new HorrorMovie(3, "The Nun", 2018, 4.0, 2));
        movies.add(new HorrorMovie(4, "The Exorcist", 1987, 5.0, 1));
        movies.add(new HorrorMovie(5, "Get Out", 2017, 5.0, 3));
        for (Movie m : movies) {
            if (m instanceof HorrorMovie) {
                System.out.println(m);
            }
        }
    }
}

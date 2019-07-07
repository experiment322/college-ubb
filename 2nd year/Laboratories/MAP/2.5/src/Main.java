import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        List<Artist> artists = new ArrayList<>();
        artists.add(new Artist(0, 23, "Bob Marley"));
        artists.add(new Artist(1, 44, "John Bon-Jovi"));
        artists.add(new Artist(2, 30, "Beyonce"));

        List<Song> songs = new ArrayList<>();
        songs.add(new Song(0, 2018, "Bum tzi bum tzi", Arrays.asList(artists.get(1), artists.get(2))));
        songs.add(new Song(1, 2004, "No woman no cry", Arrays.asList(artists.get(0))));

        for (Song s : songs) {
            if (s.getYear() == 2018) {
                System.out.println(s);
            }
        }
    }
}

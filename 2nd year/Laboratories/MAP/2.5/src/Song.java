import java.util.List;

public class Song {
    private Integer id;
    private Integer year;
    private String name;
    private List<Artist> artists;

    public Song(Integer id, Integer year, String name, List<Artist> artists) {
        this.id = id;
        this.year = year;
        this.name = name;
        this.artists = artists;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getYear() {
        return year;
    }

    public void setYear(Integer year) {
        this.year = year;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public List<Artist> getArtists() {
        return artists;
    }

    public void setArtists(List<Artist> artists) {
        this.artists = artists;
    }

    @Override
    public String toString() {
        return "Song{" +
                "id=" + id +
                ", year=" + year +
                ", name='" + name + '\'' +
                ", artists=" + artists +
                '}';
    }
}

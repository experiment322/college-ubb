import domain.Artist;
import domain.Concert;
import domain.Fan;
import repository.OnDiskRepository;
import repository.Repository;
import service.ArtistService;
import service.FanService;
import ui.UI;
import ui.tui.MainTUI;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Comparator;

public class Main {
    private static Integer getType(String genre) {
        switch (genre) {
            case "pop":
                return 1;
            case "folk":
            case "latino":
                return 2;
            case "rock":
                return 3;
            default:
                return 5;
        }
    }

    public static void main(String[] args) {
        Repository<Long, Artist> artistRepository = new OnDiskRepository<>(
                "artisti.txt",
                s -> {
                    Artist artist = new Artist();
                    artist.setId(new Long(s.split(",")[0]));
                    artist.setNume(s.split(",")[1]);
                    artist.setVarsta(new Integer(s.split(",")[2]));
                    artist.setGenMuzical(s.split(",")[3]);
                    return artist;
                }
        );
        Repository<Long, Fan> fanRepository = new OnDiskRepository<>(
                "fani.txt",
                s -> {
                    Fan fan = new Fan();
                    fan.setId(new Long(s.split(",")[0]));
                    fan.setNume(s.split(",")[1]);
                    return fan;
                }
        );
        Repository<Object, Concert> concertRepository = new OnDiskRepository<>(
                "concerte.txt",
                s -> {
                    Concert concert = new Concert();
                    concert.setId(s.split(",")[0] + "-" + s.split(",")[1]);
                    concert.setFan(fanRepository.findOne(new Long(s.split(",")[0])));
                    concert.setArtist(artistRepository.findOne(new Long(s.split(",")[1])));
                    concert.setDataConcert(
                            LocalDate.parse(s.split(",")[2].trim(), DateTimeFormatter.ISO_LOCAL_DATE)
                    );
                    return concert;
                }
        );

        // cerinta 3
        concertRepository.findAll().stream()
                .filter(concert -> concert.getFan().getNume().equals("Mihai"))
                .sorted(Comparator.comparingInt(o -> getType(o.getArtist().getGenMuzical())))
                .forEach(concert -> System.console().printf("%s\n", concert.toString()));

        // cerintele 1 si 2
        UI mainUI = new MainTUI(
                new FanService(fanRepository),
                new ArtistService(artistRepository)
        );
        mainUI.run();
    }
}

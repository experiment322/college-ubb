package ui.tui;

import service.ArtistService;

import java.util.HashMap;

class ArtistTUI extends BaseTUI {
    private ArtistService artistService;

    ArtistTUI(ArtistService artistService) {
        this.artistService = artistService;
        generateTUI(
                "Artist TUI",
                new HashMap<String, Runnable>() {{
                    put("Cauta dupa gen", ArtistTUI.this::findByGenre);
                }}
        );
    }

    private void findByGenre() {
        String genre = readOne("gen");
        artistService.findByGenre(genre)
                .forEach(artist -> System.console().printf("%s\n", artist.toString()));
    }
}

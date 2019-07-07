package ui.tui;

import service.ArtistService;
import service.FanService;

import java.util.HashMap;

public class MainTUI extends BaseTUI {
    private FanTUI fanTUI;
    private ArtistTUI artistTUI;

    public MainTUI(FanService fanService, ArtistService artistService) {
        this.fanTUI = new FanTUI(fanService);
        this.artistTUI = new ArtistTUI(artistService);
        generateTUI(
                "Main TUI",
                new HashMap<String, Runnable>() {{
                    put("Fan menu", MainTUI.this.fanTUI::run);
                    put("Artist menu", MainTUI.this.artistTUI::run);
                }});
    }
}

package ui.tui;

import service.FanService;

import java.util.HashMap;

class FanTUI extends BaseTUI {
    private FanService fanService;

    FanTUI(FanService fanService) {
        this.fanService = fanService;
        generateTUI(
                "Fan TUI",
                new HashMap<String, Runnable>() {{
                    put("Cauta ordonat dupa nume", FanTUI.this::findAllSortedByName);
                }}
        );
    }

    private void findAllSortedByName() {
        fanService.findAllSortedByName()
                .forEach(fan -> System.console().printf("%s\n", fan.toString()));
    }
}

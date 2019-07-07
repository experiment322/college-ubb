package ui.tui;

import ui.UI;

import java.util.HashMap;
import java.util.Map;

public abstract class BaseTUI implements UI {
    /**
     * Constant representing the option to exit the ui
     * It's the only option which is case sensitive
     */
    private final String EXIT_OPTION;
    /**
     * Constant by which the title is preceded
     */
    private final String TITLE_PREFIX;
    /**
     * Constant by which the every option in the list of options is preceded
     */
    private final String OPTION_PREFIX;
    /**
     * Constant representing the option prompter
     */
    private final String OPTION_PROMPT;
    /**
     * Constant representing the text to be displayed after an action is completed
     */
    private final String CONTINUE_PROMPT;
    /**
     * Constant representing the text to be displayed when no option is found for the user input
     */
    private final String INVALID_OPTION;
    // END OF CONSTANTS

    private String tui = "";
    private Map<String, Runnable> tuiMenu = new HashMap<>();

    {
        EXIT_OPTION = "EXIT";
        TITLE_PREFIX = "# ";
        OPTION_PREFIX = "- ";
        OPTION_PROMPT = "> ";
        INVALID_OPTION = "Invalid option...";
        CONTINUE_PROMPT = "Press [ENTER] to continue...";
    }

    /**
     * (Re)Generate the UI text and functionality
     * This can and should be called in the constructor of the subclasses to initialize their specific UI
     * Otherwise the user will be prompted with an empty UI
     *
     * @param tuiTitle text printed before printing all the options
     * @param tuiMenu  associations between options and functionality (command pattern)
     */
    void generateTUI(String tuiTitle, Map<String, Runnable> tuiMenu) {
        this.tuiMenu = tuiMenu;

        StringBuilder tui = new StringBuilder();
        tui.append(TITLE_PREFIX).append(tuiTitle).append("\n");
        for (String option : tuiMenu.keySet()) {
            tui.append(OPTION_PREFIX).append(option).append("\n");
        }
        tui.append(OPTION_PREFIX).append(EXIT_OPTION).append("\n").append(OPTION_PROMPT);
        this.tui = tui.toString();
    }

    /**
     * Read one string from the console
     *
     * @param key prompt representing the desired input from the user
     * @return user input
     */
    String readOne(String key) {
        return System.console().readLine("%s: ", key);
    }

    /**
     * Read multiple strings from the console
     * Calls readOne for every key in keys
     *
     * @param keys prompts for every desired input from the user
     * @return a map with values input by user and their corresponding keys
     */
    Map<String, String> readMap(String... keys) {
        Map<String, String> map = new HashMap<>();
        for (String key : keys) {
            map.put(key, readOne(key));
        }
        return map;
    }

    /**
     * General loop body displaying the UI, asking for user input
     * and then calling the corresponding functionality for the chosen option
     * The option is chosen by iterating the list of options and checking if an option contains the input string
     * The match is case insensitive and the first option found is called, ignoring the rest
     *
     * @return true if the user didn't input the EXIT_OPTION string; false otherwise
     */
    private Boolean loop() {
        String input = System.console().readLine(tui);
        if (input.equalsIgnoreCase(EXIT_OPTION)) {
            return false;
        }
        for (String option : tuiMenu.keySet()) {
            if (option.toLowerCase().contains(input.toLowerCase())) {
                System.console().printf("%s%s\n", OPTION_PROMPT, option);
                tuiMenu.get(option).run();
                return true;
            }
        }
        System.console().printf("%s\n", INVALID_OPTION);
        return true;
    }

    @Override
    public void run() {
        Boolean running = true;
        while (running) {
            System.console().printf("\n");
            try {
                running = loop();
            } catch (Exception e) {
                System.console().printf("%s: %s\n", e.getClass().getSimpleName(), e.getMessage());
            } finally {
                if (running) {
                    System.console().readPassword("%s\n", CONTINUE_PROMPT);
                }
            }
            System.console().printf("\n");
        }
    }
}

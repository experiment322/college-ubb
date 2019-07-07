package com.alex.mpp.server.service;

import com.alex.mpp.common.util.SocketManager;
import com.alex.mpp.data.domain.Game;
import com.alex.mpp.data.domain.Player;
import com.alex.mpp.data.repository.GameRepository;
import com.alex.mpp.data.repository.PlayerRepository;
import com.alex.mpp.server.util.SocketService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Service;

import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;

@Service
public class SocketMessagingService extends SocketService {
    private static final Logger LOGGER = LoggerFactory.getLogger(SocketMessagingService.class);

    private Player player;
    private final PlayerRepository playerRepository;
    private final GameRepository gameRepository;
    private final BlockingQueue<Player> playerQueue = new LinkedBlockingDeque<>();
    private final BlockingQueue<String> cmd = new LinkedBlockingDeque<>();

    protected SocketMessagingService(PlayerRepository playerRepository, GameRepository gameRepository) {
        super(SocketManager.getMessagingServerPort());
        this.playerRepository = playerRepository;
        this.gameRepository = gameRepository;
    }

    @Override
    public void run() {
        LOGGER.info("Starting notifier service on port " + this.getPort());

        try {
            this.listen(this::consumeClientException, this::consumeClientSocket);
        } catch (Exception e) {
            LOGGER.error(e.toString());
        }
    }

    private void consumeClientException(Exception e) {
        LOGGER.error(e.toString());
    }

    private void consumeClientSocket(Socket socket,
                                     ObjectOutputStream outputStream,
                                     ObjectInputStream inputStream) throws Exception {
        LOGGER.info("Client connected from " + socket.getRemoteSocketAddress());

        new Thread(() -> {
            while (true) {
                try {
                    String input = cmd.take();
                    Thread.sleep(500);
                    Integer targetId = Integer.parseInt(input.split(" ", 1)[0]);
                    String command = input.split(" ", 0)[1];
                    if (player != null && targetId.equals(player.getId())) {
                        outputStream.writeObject(command);
                    } else {
                        Thread.sleep(500);
                        cmd.put(input);
                    }
                } catch (Exception e) {
                    break;
                }
            }
        }).start();

        boolean running = true;
        while (running) {
            String command = (String) inputStream.readObject();
            System.out.println(command);
            switch (command.split(" ")[0]) {
                case "play":
                    if (player != null) break;
                    int playerId = Integer.parseInt(command.split(" ")[1]);
                    player = playerRepository.findOne(playerId);
                    if (player == null) break;
                    if (!playerQueue.isEmpty()) {
                        Player rival = playerQueue.take();
                        gameRepository.save(new Game(0, "______X__", rival.getId(), player.getId()));
                        cmd.put(player.getId() + " game ______X__ " + rival.getUsername());
                        cmd.put(rival.getId() + " game ______X__" + player.getId());
                    } else {
                        playerQueue.put(player);
                    }
                    break;
                default:
                    running = false;
            }
        }

        LOGGER.info("Client disconnected from " + socket.getRemoteSocketAddress());
    }
}

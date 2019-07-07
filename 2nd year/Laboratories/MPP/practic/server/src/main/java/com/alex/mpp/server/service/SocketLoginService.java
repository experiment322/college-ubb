package com.alex.mpp.server.service;

import com.alex.mpp.common.util.SocketManager;
import com.alex.mpp.data.domain.Player;
import com.alex.mpp.data.repository.PlayerRepository;
import com.alex.mpp.server.util.SocketService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;

@Service
public class SocketLoginService extends SocketService {
    private static final Logger LOGGER = LoggerFactory.getLogger(SocketLoginService.class);

    private final PlayerRepository playerRepository;
    private final ConcurrentHashMap<Player, List<String>> connectedClients = new ConcurrentHashMap<>();

    @Autowired
    public SocketLoginService(PlayerRepository playerRepository) {
        super(SocketManager.getLoginServerPort());
        this.playerRepository = playerRepository;
    }

    @Override
    public void run() {
        LOGGER.info("Starting login service on port " + this.getPort());

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

        String username = (String) inputStream.readObject();
        String password = (String) inputStream.readObject();

        Player player = null;
        for (Player p : playerRepository.findAll()) {
            if (p.getUsername().equals(username) && p.getPassword().equals(password)) {
                p.setPassword("");
                player = p;
            }
        }

        outputStream.writeObject(player);

        if (player != null) {
            connectedClients.computeIfAbsent(player, r -> new ArrayList<>());
            connectedClients.computeIfPresent(player, (r, clients) -> {
                String clientAddress = socket.getInetAddress().getHostAddress();
                if (!clients.contains(clientAddress)) {
                    clients.add(clientAddress);
                }
                return clients;
            });
        }

        LOGGER.info("Client disconnected from " + socket.getRemoteSocketAddress());
    }
}

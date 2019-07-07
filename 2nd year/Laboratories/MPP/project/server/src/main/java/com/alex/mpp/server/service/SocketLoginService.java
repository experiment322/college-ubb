package com.alex.mpp.server.service;

import com.alex.mpp.common.service.RefereeService;
import com.alex.mpp.common.util.SocketManager;
import com.alex.mpp.data.domain.Referee;
import com.alex.mpp.server.util.SocketService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.rmi.server.RemoteServer;
import java.rmi.server.ServerNotActiveException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;

@Service
public class SocketLoginService extends SocketService {
    private static final Logger LOGGER = LoggerFactory.getLogger(SocketLoginService.class);

    private final RefereeService refereeService;
    private final ConcurrentHashMap<Referee, List<String>> connectedClients = new ConcurrentHashMap<>();

    @Autowired
    public SocketLoginService(RefereeService refereeService) {
        super(SocketManager.getLoginServerPort());
        this.refereeService = refereeService;
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

        Referee referee = refereeService.authenticate(username, password);
        outputStream.writeObject(referee);

        if (referee != null) {
            connectedClients.computeIfAbsent(referee, r -> new ArrayList<>());
            connectedClients.computeIfPresent(referee, (r, clients) -> {
                String clientAddress = socket.getInetAddress().getHostAddress();
                if (!clients.contains(clientAddress)) {
                    clients.add(clientAddress);
                }
                return clients;
            });
        }

        LOGGER.info("Client disconnected from " + socket.getRemoteSocketAddress());
    }

    private Referee getRefereeForClient(String address) {
        return connectedClients.search(Long.MAX_VALUE,
                (referee, clients) -> clients.contains(address) ? referee : null);
    }

    boolean isRmiClientUnauthorized() {
        try {
            return getRefereeForClient(RemoteServer.getClientHost()) == null;
        } catch (ServerNotActiveException e) {
            throw new IllegalStateException(e);
        }
    }
}

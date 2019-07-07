package com.alex.mpp.server.service;

import com.alex.mpp.common.util.SocketManager;
import com.alex.mpp.server.util.SocketService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Service;

import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.Date;

@Service
public class SocketNotifierService extends SocketService {
    private static final Logger LOGGER = LoggerFactory.getLogger(SocketNotifierService.class);

    private final Date notifier = new Date();

    protected SocketNotifierService() {
        super(SocketManager.getNotifierServerPort());
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
                                     @SuppressWarnings("unused") ObjectInputStream inputStream) throws Exception {
        LOGGER.info("Client connected from " + socket.getRemoteSocketAddress());

        synchronized (notifier) {
            long timestamp = notifier.getTime();
            while (true) {
                notifier.wait();
                try {
                    if (notifier.getTime() != timestamp) {
                        timestamp = notifier.getTime();
                        outputStream.writeObject(null);
                    }
                } catch (Exception e) {
                    break;
                }
            }
        }

        LOGGER.info("Client disconnected from " + socket.getRemoteSocketAddress());
    }

    void notifyAllClients() {
        synchronized (notifier) {
            notifier.setTime(new Date().getTime());
            notifier.notifyAll();
        }
    }
}

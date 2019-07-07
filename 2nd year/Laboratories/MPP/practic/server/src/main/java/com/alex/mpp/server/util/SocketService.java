package com.alex.mpp.server.util;

import com.alex.mpp.common.util.SocketManager;
import com.alex.mpp.common.util.ThrowingTriConsumer;

import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.function.Consumer;

public abstract class SocketService implements Runnable {
    private final Integer port;

    protected SocketService(Integer port) {
        this.port = port;
        new Thread(this).start();
    }

    protected Integer getPort() {
        return port;
    }

    protected void listen(Consumer<Exception> exceptionConsumer,
                          ThrowingTriConsumer<Socket, ObjectOutputStream, ObjectInputStream> socketConsumer)
            throws Exception {
        ServerSocket serverSocket = new ServerSocket(port);

        // noinspection InfiniteLoopStatement
        while (true) {
            Socket socket = serverSocket.accept();
            new Thread(() ->
                    SocketManager.runWithSocket(socket, exceptionConsumer, socketConsumer)
            ).start();
        }
    }
}

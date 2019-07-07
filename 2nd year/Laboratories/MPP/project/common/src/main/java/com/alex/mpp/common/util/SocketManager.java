package com.alex.mpp.common.util;

import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.function.Consumer;

public class SocketManager {
    private static final String serverHostKey = "java.rmi.server.hostname";
    private static final Integer loginServerPort = 31415;
    private static final Integer notifierServerPort = 31416;

    static {
        if (System.getProperty(serverHostKey) == null) {
            System.setProperty(serverHostKey, "localhost");
        }
    }

    public static Integer getLoginServerPort() {
        return loginServerPort;
    }

    public static Integer getNotifierServerPort() {
        return notifierServerPort;
    }

    public static String getServerHost() {
        return System.getProperty(serverHostKey);
    }

    public static void runWithSocket(String host, int port,
                                     Consumer<Exception> exceptionConsumer,
                                     ThrowingTriConsumer<Socket, ObjectOutputStream, ObjectInputStream> socketConsumer) {
        try (
                Socket socket = new Socket(host, port)
        ) {
            runWithSocket(socket, exceptionConsumer, socketConsumer);
        } catch (Exception e) {
            exceptionConsumer.accept(e);
        }
    }

    public static void runWithSocket(Socket socket,
                                     Consumer<Exception> exceptionConsumer,
                                     ThrowingTriConsumer<Socket, ObjectOutputStream, ObjectInputStream> socketConsumer) {
        try (
                ObjectOutputStream outputStream = new ObjectOutputStream(socket.getOutputStream());
                ObjectInputStream inputStream = new ObjectInputStream(socket.getInputStream())
        ) {
            socketConsumer.accept(socket, outputStream, inputStream);
        } catch (Exception e) {
            exceptionConsumer.accept(e);
        }
    }
}

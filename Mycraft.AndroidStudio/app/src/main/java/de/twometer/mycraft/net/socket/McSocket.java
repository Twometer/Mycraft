package de.twometer.mycraft.net.socket;

import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;

public class McSocket {

    private static final String TAG = "McSocket";

    private Socket socket;
    private InputStream inputStream;
    private OutputStream outputStream;


    public void connect(String hostname, int port) throws IOException {
        socket = new Socket();
        socket.connect(new InetSocketAddress(hostname, port));
        inputStream = socket.getInputStream();
        outputStream = socket.getOutputStream();
    }


    public int receiveVarInt() throws IOException {
        int numRead = 0;
        int result = 0;
        byte read;
        do {
            read = (byte) inputStream.read();
            int value = (read & 0b01111111);
            result |= (value << (7 * numRead));

            numRead++;
            if (numRead > 5) {
                throw new RuntimeException("VarInt is too big");
            }
        } while ((read & 0b10000000) != 0);

        return result;
    }

    public byte[] receive(int len) throws IOException {
        byte[] buf = new byte[len];
        int total = 0;
        while (total < len) {
            int rcv = inputStream.read(buf, total, len - total);
            if (rcv <= 0) throw new IOException("Receive failed");
            total += rcv;
        }
        return buf;
    }

    public void close() throws IOException {
        socket.close();
    }

    public void send(byte[] array) throws IOException {
        outputStream.write(array);
    }


}

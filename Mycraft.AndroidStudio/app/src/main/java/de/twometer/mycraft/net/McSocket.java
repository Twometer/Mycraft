package de.twometer.mycraft.net;

import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;

import de.twometer.mycraft.net.packet.C00Handshake;
import de.twometer.mycraft.net.packet.C00KeepAlive;
import de.twometer.mycraft.net.packet.C00Login;
import de.twometer.mycraft.net.packet.IPacket;

public class McSocket {

    private static final String TAG = "McSocket";

    private Socket socket;
    private InputStream inputStream;
    private OutputStream outputStream;

    private boolean disconnectRequested = false;

    private int compressionThreshold;
    private boolean isLoginMode = true;
    private boolean doneLoadingTerrain = false;


    public void connect(String username, String hostname, int port) throws IOException {
        Log.i(TAG, "Connecting to server...");
        socket = new Socket();
        socket.connect(new InetSocketAddress(hostname, port));
        inputStream = socket.getInputStream();
        outputStream = socket.getOutputStream();
        startReceiverLoop();
        Log.i(TAG, "Logging in...");
        sendPacket(new C00Handshake(47, hostname, (short) port, 2));
        sendPacket(new C00Login(username));
    }

    private void startReceiverLoop() {
        (new Thread(new Runnable() {
            @Override
            public void run() {
                while (!disconnectRequested) {
                    try {
                        int packetLen = readVarInt();
                        if (packetLen > 0) {
                            receivePacket(packetLen);
                        }
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        })).start();
    }

    private void receivePacket(int packetLen) throws IOException {
        McBuffer buffer = new McBuffer(receive(packetLen));
        if (compressionThreshold > 0) {
            int sizeUncompressed = buffer.readVarInt();
            if (sizeUncompressed != 0) {
                byte[] old = buffer.readToEnd();
                buffer.replaceBuffer(Zlib.decompress(old, sizeUncompressed));
            }
        }
        int packetId = buffer.readVarInt();
        if (isLoginMode) {
            if (compressionThreshold == 0 && packetId == 3) {
                compressionThreshold = buffer.readVarInt();
            }
            if (packetId == 2) {
                Log.i(TAG, "Downloading terrain...");
                isLoginMode = false;
            }
        } else {
            if (packetId == 0) {
                sendPacket(new C00KeepAlive(buffer.readVarInt()));
            } else if (packetId == 8) {
                if (!doneLoadingTerrain) {
                    doneLoadingTerrain = true;
                    Log.i(TAG, "Connected.");
                }
            }
        }
    }

    private byte[] receive(int len) throws IOException {
        byte[] buf = new byte[len];
        int total = 0;
        while (total < len) {
            int rcv = inputStream.read(buf, total, len - total);
            if (rcv <= 0) throw new IOException("Receive failed");
            total += rcv;
        }
        return buf;
    }

    private int readVarInt() throws IOException {
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

    public void sendPacket(int id, byte[] data) throws IOException {
        McBuffer packetBodyBuf = new McBuffer();
        packetBodyBuf.writeVarInt(id);
        packetBodyBuf.write(data);
        byte[] packetBody = packetBodyBuf.getData();
        if (compressionThreshold > 0) {
            if (packetBody.length <= compressionThreshold) {
                packetBody = concatArrays(createVarInt(0), packetBody);
            }
        }

        byte[] packetHeader = createVarInt(packetBody.length);
        byte[] fullPacket = concatArrays(packetHeader, packetBody);
        outputStream.write(fullPacket);
    }

    public void sendPacket(IPacket packet) throws IOException {
        McBuffer buffer = new McBuffer();
        packet.write(buffer);
        sendPacket(packet.getId(), buffer.getData());
    }

    public void disconnect() {
        disconnectRequested = true;
    }

    private byte[] createVarInt(int i) {
        McBuffer buffer = new McBuffer();
        buffer.writeVarInt(i);
        return buffer.getData();
    }

    private byte[] concatArrays(byte[] a, byte[] b) {
        byte[] c = new byte[a.length + b.length];
        System.arraycopy(a, 0, c, 0, a.length);
        System.arraycopy(b, 0, c, a.length, b.length);
        return c;
    }

}

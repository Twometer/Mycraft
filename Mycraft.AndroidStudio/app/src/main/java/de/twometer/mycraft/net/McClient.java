package de.twometer.mycraft.net;

import android.util.Log;

import java.io.IOException;

import de.twometer.mycraft.net.packet.C00Handshake;
import de.twometer.mycraft.net.packet.C00KeepAlive;
import de.twometer.mycraft.net.packet.C00Login;
import de.twometer.mycraft.net.packet.IPacket;
import de.twometer.mycraft.net.socket.McBuffer;
import de.twometer.mycraft.net.socket.McSocket;
import de.twometer.mycraft.net.util.Zlib;

import static de.twometer.mycraft.net.util.ByteUtils.concatArrays;
import static de.twometer.mycraft.net.util.ByteUtils.createVarInt;

public class McClient {

    private static final String TAG = "McClient";

    private McSocket mcSocket = new McSocket();

    private boolean disconnectRequested = false;
    private int compressionThreshold;
    private boolean isLoginMode = true;
    private boolean doneLoadingTerrain = false;

    private Listener listener = new Listener() {
        @Override
        public void onPacket(int id, byte[] packet) {

        }

        @Override
        public void onLoginStatusChanged(String status) {

        }

        @Override
        public void onLoginCompleted() {

        }
    };

    public void login(String username, String hostname, int port) throws IOException {
        listener.onLoginStatusChanged("Connecting...");
        mcSocket.connect(hostname, port);
        listener.onLoginStatusChanged("Logging in...");
        sendPacket(new C00Handshake(47, hostname, (short) port, 2));
        sendPacket(new C00Login(username));
        startReceiverLoop();
    }

    private void startReceiverLoop() {
        (new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    while (!disconnectRequested) {
                        int packetLen = mcSocket.receiveVarInt();
                        if (packetLen > 0) {
                            receivePacket(packetLen);
                        }
                    }
                    mcSocket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        })).start();
    }

    private void receivePacket(int packetLen) throws IOException {
        McBuffer buffer = new McBuffer(mcSocket.receive(packetLen));
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
                listener.onLoginStatusChanged("Downloading terrain...");
                isLoginMode = false;
            }
        } else {
            if (packetId == 0) {
                sendPacket(new C00KeepAlive(buffer.readVarInt()));
                return;
            }
            if (packetId == 8) {
                if (!doneLoadingTerrain) {
                    doneLoadingTerrain = true;
                    listener.onLoginCompleted();
                }
            }
            listener.onPacket(packetId, buffer.readToEnd());
        }
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
        mcSocket.send(fullPacket);
    }

    public void sendPacket(IPacket packet) throws IOException {
        McBuffer buffer = new McBuffer();
        packet.write(buffer);
        sendPacket(packet.getId(), buffer.getData());
    }

    public void disconnect() {
        disconnectRequested = true;
    }

    public void setListener(Listener listener) {
        this.listener = listener;
    }
}

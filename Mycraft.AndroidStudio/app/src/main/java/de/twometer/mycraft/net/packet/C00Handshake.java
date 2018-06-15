package de.twometer.mycraft.net.packet;

import java.io.IOException;

import de.twometer.mycraft.net.socket.McBuffer;

public class C00Handshake implements IPacket {

    private int protocolVersion;
    private String hostname;
    private short port;
    private int nextState;

    public C00Handshake(int protocolVersion, String hostname, short port, int nextState) {
        this.protocolVersion = protocolVersion;
        this.hostname = hostname;
        this.port = port;
        this.nextState = nextState;
    }

    @Override
    public void write(McBuffer buffer) throws IOException {
        buffer.writeVarInt(protocolVersion);
        buffer.writeString(hostname);
        buffer.writeUshort(port);
        buffer.writeVarInt(nextState);
    }

    @Override
    public void read(McBuffer buffer) throws IOException {

    }

    @Override
    public int getId() {
        return 0;
    }
}

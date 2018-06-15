package de.twometer.mycraft.net.packet;

import java.io.IOException;

import de.twometer.mycraft.net.socket.McBuffer;

public class C00KeepAlive implements IPacket {

    public int value;

    public C00KeepAlive(int value) {
        this.value = value;
    }

    @Override
    public void write(McBuffer buffer) throws IOException {
        buffer.writeVarInt(value);
    }

    @Override
    public void read(McBuffer buffer) throws IOException {

    }

    @Override
    public int getId() {
        return 0;
    }
}

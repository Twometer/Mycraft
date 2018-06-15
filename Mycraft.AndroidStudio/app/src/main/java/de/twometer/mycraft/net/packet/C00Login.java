package de.twometer.mycraft.net.packet;

import java.io.IOException;

import de.twometer.mycraft.net.socket.McBuffer;

public class C00Login implements IPacket {

    private String username;

    public C00Login(String username) {
        this.username = username;
    }

    @Override
    public void write(McBuffer buffer) throws IOException {
        buffer.writeString(username);
    }

    @Override
    public void read(McBuffer buffer) throws IOException {
        username = buffer.readString();
    }

    @Override
    public int getId() {
        return 0;
    }
}

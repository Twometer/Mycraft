package de.twometer.mycraft.net.packet;

import java.io.IOException;

import de.twometer.mycraft.net.socket.McBuffer;

public class C05PlayerLook implements IPacket {

    private float yaw;
    private float pitch;
    private boolean onGround;

    public C05PlayerLook(float yaw, float pitch, boolean onGround) {
        this.yaw = yaw;
        this.pitch = pitch;
        this.onGround = onGround;
    }

    @Override
    public void write(McBuffer buffer) throws IOException {
        buffer.writeFloat(yaw);
        buffer.writeFloat(pitch);
        buffer.writeBoolean(onGround);
    }

    @Override
    public void read(McBuffer buffer) throws IOException {

    }

    @Override
    public int getId() {
        return 5;
    }
}

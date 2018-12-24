package de.twometer.mycraft.net.packet;

import java.io.IOException;

import de.twometer.mycraft.net.socket.McBuffer;

public class C06PlayerPosLook implements IPacket {

    private double x;
    private double y;
    private double z;
    private float yaw;
    private float pitch;
    private boolean onGround;

    public C06PlayerPosLook(double x, double y, double z, float yaw, float pitch, boolean onGround) {
        this.x = x;
        this.y = y;
        this.z = z;
        this.yaw = yaw;
        this.pitch = pitch;
        this.onGround = onGround;
    }

    @Override
    public void write(McBuffer buffer) throws IOException {
        buffer.writeDouble(x);
        buffer.writeDouble(y);
        buffer.writeDouble(z);
        buffer.writeFloat(yaw);
        buffer.writeFloat(pitch);
        buffer.writeBoolean(onGround);
    }

    @Override
    public void read(McBuffer buffer) throws IOException {

    }

    @Override
    public int getId() {
        return 6;
    }
}

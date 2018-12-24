package de.twometer.mycraft.net.packet;

import java.io.IOException;

import de.twometer.mycraft.net.socket.McBuffer;

public class C04PlayerPosition implements IPacket {

    private double x;
    private double y;
    private double z;
    private boolean onGround;

    public C04PlayerPosition(double x, double y, double z, boolean onGround) {
        this.x = x;
        this.y = y;
        this.z = z;
        this.onGround = onGround;
    }

    @Override
    public void write(McBuffer buffer) throws IOException {
        buffer.writeDouble(x);
        buffer.writeDouble(y);
        buffer.writeDouble(z);
        buffer.writeBoolean(onGround);
    }

    @Override
    public void read(McBuffer buffer) throws IOException {

    }

    @Override
    public int getId() {
        return 4;
    }
}

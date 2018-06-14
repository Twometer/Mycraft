package de.twometer.mycraft.net.packet;

import java.io.IOException;

import de.twometer.mycraft.net.McBuffer;

public interface IPacket {

    void write(McBuffer buffer) throws IOException;
    void read(McBuffer buffer) throws IOException;
    int getId();

}

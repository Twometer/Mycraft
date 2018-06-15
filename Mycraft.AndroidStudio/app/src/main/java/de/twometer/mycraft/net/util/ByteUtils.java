package de.twometer.mycraft.net.util;

import de.twometer.mycraft.net.socket.McBuffer;

public class ByteUtils {

    public static byte[] createVarInt(int i) {
        McBuffer buffer = new McBuffer();
        buffer.writeVarInt(i);
        return buffer.getData();
    }

    public static byte[] concatArrays(byte[] a, byte[] b) {
        byte[] c = new byte[a.length + b.length];
        System.arraycopy(a, 0, c, 0, a.length);
        System.arraycopy(b, 0, c, a.length, b.length);
        return c;
    }

}

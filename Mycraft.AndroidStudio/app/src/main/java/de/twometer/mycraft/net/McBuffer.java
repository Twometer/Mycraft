package de.twometer.mycraft.net;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;

public class McBuffer {

    private ByteArrayInputStream inputStream;
    private ByteArrayOutputStream outputStream;

    public McBuffer(byte[] input) {
        inputStream = new ByteArrayInputStream(input);
    }

    public McBuffer() {
        outputStream = new ByteArrayOutputStream();
    }

    public void replaceBuffer(byte[] newBuffer) {
        inputStream = new ByteArrayInputStream(newBuffer);
    }

    public int readVarInt() {
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

    public byte[] readToEnd() throws IOException {
        return read(inputStream.available());
    }

    public String readString() throws IOException {
        return new String(read(readVarInt()));
    }

    public void writeUshort(short s) throws IOException {
        write(ByteBuffer.allocate(2).putShort(s).array());
    }

    public void writeString(String string) throws IOException {
        byte[] bt = string.getBytes();
        writeVarInt(bt.length);
        write(bt);
    }

    private byte[] read(int len) throws IOException {
        byte[] buf = new byte[len];
        if (inputStream.read(buf) > 0)
            return buf;
        else throw new IOException("End of buffer reached");
    }

    public void write(byte[] buf) throws IOException {
        outputStream.write(buf);
    }

    public void writeVarInt(int value) {
        do {
            byte temp = (byte) (value & 0b01111111);
            // Note: >>> means that the sign bit is shifted with the rest of the number rather than being left alone
            value >>>= 7;
            if (value != 0) {
                temp |= 0b10000000;
            }
            outputStream.write(temp);
        } while (value != 0);
    }

    public byte[] getData() {
        return outputStream.toByteArray();
    }

}

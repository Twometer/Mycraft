package de.twometer.mycraft.net;

import java.util.zip.DataFormatException;
import java.util.zip.Inflater;

public class Zlib {

    public static byte[] decompress(byte[] toDecompress, int sizeUncompressed) {
        byte[] output = new byte[sizeUncompressed];
        Inflater inflater = new Inflater();
        inflater.setInput(toDecompress);
        try {
            inflater.inflate(output);
        } catch (DataFormatException e) {
            e.printStackTrace();
        }
        inflater.end();
        return output;
    }

}

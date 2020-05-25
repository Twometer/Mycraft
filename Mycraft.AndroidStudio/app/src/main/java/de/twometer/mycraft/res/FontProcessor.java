package de.twometer.mycraft.res;

import android.graphics.Bitmap;

public class FontProcessor {

    public static byte[] measureFont(Bitmap bitmap) {
        byte[] widths = new byte[256];
        for (int i = 0; i < 256; i++) {
            int x = (i % 16) * 8;
            int y = (i >> 4) * 8;
            int width = 0;
            for (int y_ = 0; y_ < 8; y_++) {
                int minX = 1000;
                int maxX = -1000;
                for (int x_ = 0; x_ < 8; x_++) {
                    int color = bitmap.getPixel(x_ + x, y_ + y);
                    float a = ((color >> 24) & 0xff) / 255.0f;
                    if (a != 0) {
                        if (x_ < minX) minX = x_;
                        if (x_ > maxX) maxX = x_ + 1;
                    }
                }
                int tempWidth = maxX - minX;
                if (tempWidth > width) width = tempWidth;
            }
            if (width == 0) width = 2; // Blank char
            widths[i] = (byte) (width);
        }
        return widths;
    }

}

package de.twometer.mycraft.interop;

public class NativeLib {

    static {
        System.loadLibrary("native-lib");
    }

    public native void register(JavaCallback callback);

    public native void onPacket(int id, byte[] packet);

    public native void onLoginCompleted();

    public native void onSurfaceCreated();

    public native void onSurfaceChanged(int width, int height);

    public native void onDrawFrame();

    public native void setAssetsFolder(String folder);

    public native void onRotate(float dx, float dy);

    public native void onPadTouch(boolean down, float x, float y);

    public native void onTouch(boolean down, float x, float y);

    public native void uploadFontWidths(byte[] widths);

}

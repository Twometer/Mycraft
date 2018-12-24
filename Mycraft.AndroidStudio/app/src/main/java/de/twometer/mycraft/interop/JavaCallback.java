package de.twometer.mycraft.interop;

public interface JavaCallback {

    void setPosition(double x, double y, double z);
    void setRotation(float yaw, float pitch);
    void setPosAndRot(double x, double y, double z, float yaw, float pitch);

}

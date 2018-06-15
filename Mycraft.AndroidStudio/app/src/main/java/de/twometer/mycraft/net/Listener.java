package de.twometer.mycraft.net;

public interface Listener {

    void onPacket(int id, byte[] packet);

    void onLoginStatusChanged(String status);

    void onLoginCompleted();

}

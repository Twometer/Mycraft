//
// Created by twome on 21/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_PACKETHANDLER_H
#define MYCRAFT_ANDROIDSTUDIO_PACKETHANDLER_H


class PacketHandler {
public:
    void onPacket(int id, unsigned char *content, int contentLength);
};


#endif //MYCRAFT_ANDROIDSTUDIO_PACKETHANDLER_H

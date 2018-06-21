//
// Created by twome on 21/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_PACKETBUFFER_H
#define MYCRAFT_ANDROIDSTUDIO_PACKETBUFFER_H


class PacketBuffer {
private:
    unsigned char *buf;
    int allocated;
    int inputSize;
    int readOffset;
public:
    PacketBuffer();

    PacketBuffer(unsigned char *buffer, int size);

    unsigned char readByte();

    bool readBool();

    unsigned short readUShort();

    int readVarInt();

    int readInt();

    double readDouble();

    void readArray(unsigned char *target, int length);

    unsigned char *getDataPointer();

    void skip(int len);;
};


#endif //MYCRAFT_ANDROIDSTUDIO_PACKETBUFFER_H

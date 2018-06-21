//
// Created by twome on 21/06/2018.
//

#include "PacketBuffer.h"
#include <algorithm>
#include <cstring>

#define DOUBLE_SIZE 8
#define INT_SIZE 4
#define SHORT_SIZE 2

using namespace std;

PacketBuffer::PacketBuffer() {

}

PacketBuffer::PacketBuffer(unsigned char *buffer, int size) {
    this->buf = buffer;
    this->inputSize = size;
    this->readOffset = 0;
}

unsigned char PacketBuffer::readByte() {
    unsigned char byte = buf[readOffset];
    readOffset++;
    return byte;
}

bool PacketBuffer::readBool() {
    return readByte();
}

unsigned short PacketBuffer::readUShort() {
    unsigned short value = 0;
    unsigned char *tmp = new unsigned char[SHORT_SIZE];
    readArray(tmp, SHORT_SIZE);
    reverse(tmp, tmp + SHORT_SIZE);
    memcpy(&value, tmp, SHORT_SIZE);
    return value;
}

int PacketBuffer::readVarInt() {
    int i = 0;
    int j = 0;
    int k = 0;
    while (true) {
        k = (int) readByte();
        i |= (k & 0x7F) << j++ * 7;
        if (j > 5) return 0;
        if ((k & 0x80) != 128) break;
    }
    return i;
}

int PacketBuffer::readInt() {
    int value = 0;
    unsigned char *tmp = new unsigned char[INT_SIZE];
    readArray(tmp, INT_SIZE);
    reverse(tmp, tmp + INT_SIZE);
    memcpy(&value, tmp, INT_SIZE);
    return value;
}

void PacketBuffer::readArray(unsigned char *target, int length) {
    memcpy(target, buf + readOffset, static_cast<size_t>(length));
    readOffset += length;
}

double PacketBuffer::readDouble() {
    double value = 0;
    unsigned char *tmp = new unsigned char[DOUBLE_SIZE];
    readArray(tmp, DOUBLE_SIZE);
    reverse(tmp, tmp + DOUBLE_SIZE);
    memcpy(&value, tmp, DOUBLE_SIZE);
    return value;
}

unsigned char *PacketBuffer::getDataPointer() {
    return buf + readOffset;
}

void PacketBuffer::skip(int len) {
    readOffset += len;
}

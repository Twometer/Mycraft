//
// Created by twome on 17/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_CHUNK_H
#define MYCRAFT_ANDROIDSTUDIO_CHUNK_H


#include "Section.h"

class Chunk {
private:
    Section **sections;
public:
    int x;
    int z;

    Chunk(int x, int z);

    void render(int pass);

    void setBlock(int x, int y, int z, uint8_t block);

    unsigned char getBlock(int x, int y, int z);

    int loadFromPacket(uint8_t* data, uint8_t bitmask);

    void reload();
};


#endif //MYCRAFT_ANDROIDSTUDIO_CHUNK_H

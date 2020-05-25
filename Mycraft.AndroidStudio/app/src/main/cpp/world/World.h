//
// Created by twome on 17/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_WORLD_H
#define MYCRAFT_ANDROIDSTUDIO_WORLD_H

#define RENDERPASS_SOLID 1
#define RENDERPASS_FLUID 2

#include "Chunk.h"
#include "AABB.h"
#include <vector>

class World {
private:
    Chunk **chunkArray;
    int chunkArrayLen;

public:
    void render(int pass);

    void setBlock(int x, int y, int z, uint8_t block);

    uint8_t getBlock(int x, int y, int z);

    void addChunk(Chunk *chunk);

    std::vector<AABB> getCubes(int x, int y, int z, int r);

    void reload();

    World();
};


#endif //MYCRAFT_ANDROIDSTUDIO_WORLD_H

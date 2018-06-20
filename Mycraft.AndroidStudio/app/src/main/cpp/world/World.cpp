//
// Created by twome on 17/06/2018.
//

#include <cstdlib>
#include "World.h"
#include "../Renderer.h"

#define RENDER_DISTANCE 8

World::World() {
    chunkArray = new Chunk *[1024];
    for (int i = 0; i < chunkArrayLen; i++)
        chunkArray[i] = NULL;
}


void World::render(int pass) {
    glm::vec3 pos = Renderer::getPlayer()->getPosition();
    int chX = (int) pos.x >> 4;
    int chZ = (int) pos.z >> 4;
    for (int i = 0; i < chunkArrayLen; i++) {
        Chunk *chkPtr = chunkArray[i];
        if (chkPtr == NULL) continue;
        if (glm::abs(chkPtr->x - chX) > RENDER_DISTANCE ||
            glm::abs(chkPtr->z - chZ) > RENDER_DISTANCE)
            continue;
        chkPtr->render(pass);
    }
}

void World::setBlock(int x, int y, int z, unsigned char block) {
    if (y < 0 || y > 255) return;
    int chunkX = x >> 4;
    int chunkZ = z >> 4;
    for (int i = 0; i < chunkArrayLen; i++) {
        Chunk *chkPtr = chunkArray[i];
        if (chkPtr == NULL) continue;
        Chunk chk = *chkPtr;
        if (chk.x != chunkX || chk.z != chunkZ) continue;
        chk.setBlock(x & 15, y, z & 15, block);
        return;
    }
}

unsigned char World::getBlock(int x, int y, int z) {
    if (y < 0 || y > 255) return 0;
    int chunkX = x >> 4;
    int chunkZ = z >> 4;
    for (int i = 0; i < chunkArrayLen; i++) {
        Chunk *chkPtr = chunkArray[i];
        if (chkPtr == NULL) continue;
        Chunk chk = *chkPtr;
        if (chk.x != chunkX || chk.z != chunkZ) continue;
        return chk.getBlock(x & 15, y, z & 15);
    }
    return 0;
}

void World::addChunk(Chunk *chunk) {
    chunkArray[chunkArrayLen] = chunk;
    chunkArrayLen++;
}

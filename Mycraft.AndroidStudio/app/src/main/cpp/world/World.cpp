//
// Created by twome on 17/06/2018.
//

#include <cstdlib>
#include "World.h"
#include "../Renderer.h"
#include "../block/BlockRegistry.h"

#define RENDER_DISTANCE 10

World::World() {
    chunkArray = new Chunk *[1024];
    for (int i = 0; i < 1024; i++)
        chunkArray[i] = NULL;
    chunkArrayLen = 0;
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

void World::setBlock(int x, int y, int z, uint8_t block) {
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

uint8_t World::getBlock(int x, int y, int z) {
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

std::vector<AABB> World::getCubes(int xx, int xy, int xz, int r) {
    std::vector<AABB> cubes = std::vector<AABB>();
    for (int x = -r; x <= r; x++) {
        for (int y = -r; y <= r; y++) {
            for (int z = -r; z <= r; z++) {
                uint8_t bid = getBlock(xx + x, xy + y, xz + z);
                Block *block = BlockRegistry::getBlock(bid);

                if (block != nullptr && !block->noClip) {
                    AABB boundingBox = AABB(glm::vec3(xx + x, xy + y, xz + z),
                                            glm::vec3(xx + x, xy + y, xz + z));
                    boundingBox = boundingBox.expand(1.0, bid == 78 ? 0.1 : 1.0, 1.0);
                    cubes.push_back(boundingBox);
                }
            }
        }
    }
    return cubes;
}

void World::reload() {
    for (int i = 0; i < chunkArrayLen; i++) {
        Chunk *chk = chunkArray[i];
        if (chk != NULL)
            chk->reload();
    }
}

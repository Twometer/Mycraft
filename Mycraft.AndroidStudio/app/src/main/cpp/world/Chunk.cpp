//
// Created by twome on 17/06/2018.
//

#include <cstdlib>
#include "Chunk.h"

Chunk::Chunk(int x, int z) {
    this->x = x;
    this->z = z;
    sections = new Section *[16];
    for (int i = 0; i < 16; i++)
        sections[i] = NULL;
}

void Chunk::setBlock(int x, int y, int z, unsigned char block) {
    int sectionIdx = y >> 4;
    Section *section = sections[sectionIdx];
    if (section == NULL) {
        if (block == 0)
            return;
        section = new Section(this->x, sectionIdx, this->z);
        sections[sectionIdx] = section;
    }
    section->setBlock(x, y & 15, z, block);
}

unsigned char Chunk::getBlock(int x, int y, int z) {
    int sectionIdx = y >> 4;
    Section *section = sections[sectionIdx];
    if (section == NULL) return 0;
    return section->getBlock(x, y & 15, z);
}

void Chunk::render(int pass) {
    for (int i = 0; i < 16; i++) {
        Section *section = sections[i];
        if (section != NULL && section->isInFrustum())
            section->render(pass);
    }
}

int Chunk::loadFromPacket(unsigned char *data, unsigned short bitmask) {
    int idx = 0;
    for (int i = 0; i < 16; i++) {
        if ((bitmask & (1 << i)) != 0) {
            Section *section = sections[i];
            if (section == NULL) {
                section = new Section(this->x, i, this->z);
                sections[i] = section;
                for (int y = 0; y < 16; y++) {
                    for (int z = 0; z < 16; z++) {
                        for (int x = 0; x < 16; x++) {
                            unsigned char blockId = (unsigned char) (
                                    ((data[idx + 1] & 255) << 8 | data[idx] & 255) >> 4);
                            if (blockId != 0)
                                section->setBlock(x, y, z, blockId);
                            idx += 2;
                        }
                    }
                }
            }
        }
    }
    return idx;
}

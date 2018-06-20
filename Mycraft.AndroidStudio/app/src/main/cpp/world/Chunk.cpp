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

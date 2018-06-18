//
// Created by twome on 17/06/2018.
//

#include "Section.h"
#include "../render/AsyncSectionQueue.h"

Section::Section(int x, int idx, int z) {
    data = new unsigned char[dataLen];
    dataLen = 16 * 16 * 16;

    this->x = x;
    this->idx = idx;
    this->z = z;

    this->sectionRenderer = new SectionRenderer(this);
}

void Section::render(int pass) {
    if (state == STATE_SHOULD_BUILD) {
        state = STATE_AWAITING_BUILD;
        AsyncSectionQueue::schedule(this);
    } else if (state == STATE_SHOULD_UPLOAD) {
        sectionRenderer->uploadData();
        state = STATE_SHOULD_RENDER;
    } else if (state == STATE_SHOULD_RENDER) {
        sectionRenderer->render();
    }
}

void Section::setBlock(int x, int y, int z, unsigned char block) {
    int idx = (y * 16 + z) * 16 + x;
    if (idx >= 0 && idx < dataLen)
        data[idx] = block;
}

unsigned char Section::getBlock(int x, int y, int z) {
    int idx = (y * 16 + z) * 16 + x;
    if (idx >= 0 && idx < dataLen)
        return data[idx];
    else return 0;
}

void Section::setState(int state) {
    this->state = state;
}

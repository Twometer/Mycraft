//
// Created by twome on 17/06/2018.
//

#include "Section.h"
#include "../render/AsyncSectionQueue.h"
#include "../Renderer.h"

Section::Section(int x, int idx, int z) {
    dataLen = 4096;
    data = new unsigned char[dataLen];
    memset(data, 0, static_cast<size_t>(dataLen));

    this->x = x;
    this->idx = idx;
    this->z = z;

    this->worldXCenter = (x << 4) + 8;
    this->worldYCenter = (idx << 4) + 8;
    this->worldZCenter = (z << 4) + 8;

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

void Section::setBlock(int x, int y, int z, uint8_t block) {
    int idx = (y * 16 + z) * 16 + x;
    if (idx >= 0 && idx < dataLen)
        data[idx] = block;
}

uint8_t Section::getBlock(int x, int y, int z) {
    int idx = (y * 16 + z) * 16 + x;
    if (idx >= 0 && idx < dataLen)
        return data[idx];
    else return 0;
}

void Section::setState(int state) {
    this->state = state;
}

bool Section::isInFrustum() {
    return Renderer::isCubeInFrustum(worldXCenter, worldYCenter, worldZCenter, 8);
}

void Section::reload() {
    if (state == STATE_SHOULD_RENDER) {
        sectionRenderer->reinitialize();
        state = STATE_SHOULD_BUILD;
    }
}

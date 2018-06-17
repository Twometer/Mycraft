//
// Created by twome on 17/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_SECTION_H
#define MYCRAFT_ANDROIDSTUDIO_SECTION_H

#include "../render/SectionRenderer.h"

#define STATE_SHOULD_BUILD 1
#define STATE_AWAITING_BUILD 2
#define STATE_SHOULD_UPLOAD 3
#define STATE_SHOULD_RENDER 4

class SectionRenderer;
class Section {
private:
    unsigned char *data;
    int dataLen;
    int state = STATE_SHOULD_BUILD;
public:

    int x;
    int idx;
    int z;

    SectionRenderer* sectionRenderer;

    Section(int x, int idx, int z);

    void render(int pass);

    void setBlock(int x, int y, int z, unsigned char block);

    unsigned char getBlock(int x, int y, int z);

    void setState(int state);

};


#endif //MYCRAFT_ANDROIDSTUDIO_SECTION_H

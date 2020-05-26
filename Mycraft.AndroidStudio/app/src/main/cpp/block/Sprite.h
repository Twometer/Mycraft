//
// Created by twome on 17/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_SPRITE_H
#define MYCRAFT_ANDROIDSTUDIO_SPRITE_H

/**
 * Defines a sprite position in the
 * block texture atlas
 */
struct Sprite {
    int x;
    int y;

    Sprite() {
    }

    Sprite(int x, int y) : x(x), y(y) {
    }
};

#endif //MYCRAFT_ANDROIDSTUDIO_SPRITE_H

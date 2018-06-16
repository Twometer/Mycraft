//
// Created by twome on 16/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_CAMERA_H
#define MYCRAFT_ANDROIDSTUDIO_CAMERA_H


#include "Player.h"
#include "Renderer.h"

class Camera {

private:
    Player *player;
    Renderer *renderer;
public:
    Camera(Player *player, Renderer *renderer);

    glm::mat4 compute();

};


#endif //MYCRAFT_ANDROIDSTUDIO_CAMERA_H

//
// Created by twome on 16/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_CAMERA_H
#define MYCRAFT_ANDROIDSTUDIO_CAMERA_H


#include "Player.h"
#include "Renderer.h"
#include "Frustum.h"

class Renderer;
class Camera {

private:
    Player *player;
    Renderer *renderer;
    Frustum frustum;
public:
    Camera(Player *player, Renderer *renderer);

    glm::mat4 compute();

    Frustum getFrustum();
};


#endif //MYCRAFT_ANDROIDSTUDIO_CAMERA_H

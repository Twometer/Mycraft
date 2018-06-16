//
// Created by twome on 16/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_PLAYER_H
#define MYCRAFT_ANDROIDSTUDIO_PLAYER_H

#include "glm/glm.hpp"

class Player {
private:
    float posX;
    float posY ;
    float posZ ;
    float yaw ;
    float pitch;
public:
    glm::vec3 getPosition();

    glm::vec3 getEyePosition();

    glm::vec2 getRotation();

    void rotate(float dx, float dy);

    void move(float dx, float dy, float dz);
};


#endif //MYCRAFT_ANDROIDSTUDIO_PLAYER_H

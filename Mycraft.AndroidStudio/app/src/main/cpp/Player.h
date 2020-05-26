//
// Created by twome on 16/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_PLAYER_H
#define MYCRAFT_ANDROIDSTUDIO_PLAYER_H

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "gui/ControlPad.h"

#define GRAVITY 0.07f
#define SLIPPERINESS 0.61f
#define PHYSICS_DELAY 10

class Player {
private:
    float posX;
    float posY;
    float posZ;
    float lastTickPosX;
    float lastTickPosY;
    float lastTickPosZ;
    float motionX;
    float motionY;
    float motionZ;
    float yaw;
    float pitch;
    int jumpTicks;
    bool onGround;
    bool doPhysics;
public:
    glm::vec3 getPosition();

    glm::vec3 getEyePositionInterpolated();

    glm::vec2 getRotation();

    void rotate(float dx, float dy);

    void move(float dx, float dy, float dz);

    void setPosition(float x, float y, float z);

    void jump();

    void startPhysics();

    void tick(ControlPad *pad);

private:
    void sendToServer();
};


#endif //MYCRAFT_ANDROIDSTUDIO_PLAYER_H

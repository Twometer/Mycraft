//
// Created by twome on 16/06/2018.
//

#include "Player.h"
#include "glm/gtc/constants.hpp"

glm::vec3 Player::getPosition() {
    return glm::vec3(posX, posY, posZ);
}

glm::vec3 Player::getEyePosition() {
    return glm::vec3(posX, posY + 1.73f, posZ);
}

glm::vec2 Player::getRotation() {
    return glm::vec2(yaw, pitch);
}

void Player::rotate(float dx, float dy) {
    yaw += dx;
    pitch += dy;
    if (pitch > 90) pitch = 90;
    else if (pitch < -90)pitch = -90;
}

void Player::move(float dx, float dy, float dz) {
    posX += dx;
    posY += dy;
    posZ += dz;
}

void Player::tick(ControlPad *pad) {

    float yawRad = glm::radians(yaw);

    glm::vec3 direction(
            glm::sin(yawRad),
            0,
            glm::cos(yawRad)
    );

    float piOver2 = glm::pi<float>() / 2.f;

    glm::vec3 right(
            glm::sin(yawRad - piOver2),
            0,
            glm::cos(yawRad - piOver2)
    );

    direction *= .2;
    right *= .2;

    if (pad->pressedKey == CONTROL_FORWARD) {
        move(direction.x, direction.y, direction.z);
    } else if (pad->pressedKey == CONTROL_BACKWARD) {
        move(-direction.x, -direction.y, -direction.z);
    } else if (pad->pressedKey == CONTROL_RIGHT) {
        move(right.x, right.y, right.z);
    } else if (pad->pressedKey == CONTROL_LEFT) {
        move(-right.x, -right.y, -right.z);
    } else if (pad->pressedKey == CONTROL_JUMP) {
        move(0, .2, 0);
    }
}

//
// Created by twome on 16/06/2018.
//

#include "Player.h"

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

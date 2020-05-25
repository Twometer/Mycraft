//
// Created by twome on 16/06/2018.
//

#include "Player.h"
#include "glm/gtc/constants.hpp"
#include "glm/glm.hpp"
#include "world/AABB.h"
#include "Renderer.h"
#include "JavaCallbacks.h"

glm::vec3 Player::getPosition() {
    return glm::vec3(posX, posY, posZ);
}

glm::vec3 Player::getEyePositionInterpolated() {
    float partialTicks = Renderer::getTickEngine()->partialTicks;
    return glm::vec3(lastTickPosX + (posX - lastTickPosX) * partialTicks,
                     lastTickPosY + (posY - lastTickPosY) * partialTicks + 1.73f,
                     lastTickPosZ + (posZ - lastTickPosZ) * partialTicks);
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
    AABB playerBox = AABB(glm::vec3(posX - 0.33, posY, posZ - 0.33),
                          glm::vec3(posX + 0.33, posY + 1.9, posZ + 0.33));
    std::vector<AABB> collision = Renderer::getWorld()->getCubes(
            static_cast<int>(glm::floor(posX)), static_cast<int>(glm::floor(posY)),
            static_cast<int>(glm::floor(posZ)), 4);

    double xaOrg = dx;
    double yaOrg = dy;
    double zaOrg = dz;
    for (unsigned int i = 0; i < collision.size(); i++) {
        dy = static_cast<float>(collision.at(i).clipYCollide(playerBox, dy));
    }
    playerBox.move(0, dy, 0);
    for (unsigned int i = 0; i < collision.size(); i++) {
        dx = static_cast<float>(collision.at(i).clipXCollide(playerBox, dx));
    }
    playerBox.move(dx, 0, 0);
    for (unsigned int i = 0; i < collision.size(); i++) {
        dz = static_cast<float>(collision.at(i).clipZCollide(playerBox, dz));
    }
    playerBox.move(0, 0, dz);

    this->onGround = dy != yaOrg && yaOrg < 0.0;

    if (xaOrg != dx) motionX = 0.0f;
    if (yaOrg != dy) motionY = 0.0f;
    if (zaOrg != dz) motionZ = 0.0f;

    if (xaOrg != dx || zaOrg != dz)
        jump();

    posX = (playerBox.p0.x + playerBox.p1.x) / 2;
    posY = playerBox.p0.y;
    posZ = (playerBox.p0.z + playerBox.p1.z) / 2;
}


void Player::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

int physicsEnabledTicks = 0;

void Player::tick(ControlPad *pad) {
    //// PHYSICS ////
    lastTickPosX = posX;
    lastTickPosY = posY;
    lastTickPosZ = posZ;
    if (jumpTicks > 0)
        jumpTicks--;

    move(motionX, motionY, motionZ);

    if (doPhysics && physicsEnabledTicks <= PHYSICS_DELAY)
        physicsEnabledTicks++;

    if (doPhysics && physicsEnabledTicks > PHYSICS_DELAY) {
        motionX *= SLIPPERINESS;
        motionY -= GRAVITY;
        motionZ *= SLIPPERINESS;
    }

    //// INPUT ////
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

    float xa = 0.0f;
    float za = 0.0f;
    if (pad->pressedKey == CONTROL_FORWARD) {
        xa += direction.x;
        za += direction.z;
    } else if (pad->pressedKey == CONTROL_BACKWARD) {
        xa -= direction.x;
        za -= direction.z;
    } else if (pad->pressedKey == CONTROL_RIGHT) {
        xa += right.x;
        za += right.z;
    } else if (pad->pressedKey == CONTROL_LEFT) {
        xa -= right.x;
        za -= right.z;
    } else if (pad->pressedKey == CONTROL_JUMP) {
        jump();
    }

    if (xa != 0) motionX = xa;
    if (za != 0) motionZ = za;

    //// SERVER UPDATE ////
    sendToServer();
}


void Player::jump() {
    if (onGround && jumpTicks == 0) {
        jumpTicks = 4;
        motionY = 0.42f;
    }
}

void Player::startPhysics() {

    doPhysics = true;

}

void Player::sendToServer() {
    JavaCallbacks::setPosition(posX, posY, posZ);
}

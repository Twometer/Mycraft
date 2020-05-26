//
// Created by twome on 16/06/2018.
//

#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

const float FOV = 70;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 2000.f;

Camera::Camera(Player *player, Renderer *renderer) {
    this->player = player;
    this->renderer = renderer;
    this->frustum = Frustum();
}

glm::mat4 Camera::compute() {
    Player player = *this->player;
    glm::vec2 rotation = player.getRotation();
    glm::vec3 position = player.getEyePositionInterpolated();
    float yaw = glm::radians(rotation.x);
    float pitch = glm::radians(rotation.y);

    glm::vec3 direction(
            glm::cos(pitch) * glm::sin(yaw),
            glm::sin(pitch),
            glm::cos(pitch) * glm::cos(yaw)
    );

    glm::vec3 right(
            sin(yaw - 1.5707f),
            0,
            cos(yaw - 1.5707f)
    );

    glm::vec3 up = cross(right, direction);

    glm::mat4 modelMatrix(1.0f);

    glm::vec2 viewportSize = renderer->getSize();
    float aspectRatio = viewportSize.x / viewportSize.y;

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(FOV), aspectRatio, NEAR_PLANE,
                                                  FAR_PLANE);

    glm::mat4 viewMatrix = lookAt(
            position,
            position + direction,
            up
    );

    glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
    frustum.calculate(mvpMatrix);
    return mvpMatrix;
}

Frustum Camera::getFrustum() {
    return frustum;
}

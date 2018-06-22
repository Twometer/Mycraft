//
// Created by twome on 16/06/2018.
//

#include "Camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

const float FOV = 70;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 2000.f;

Camera::Camera(Player *player, Renderer *renderer) {
    this->player = player;
    this->renderer = renderer;
    this->frustum = Frustum();
}

mat4 Camera::compute() {
    Player player = *this->player;
    vec2 rotation = player.getRotation();
    vec3 position = player.getEyePositionInterpolated();
    float yaw = radians(rotation.x);
    float pitch = radians(rotation.y);

    vec3 direction(
            glm::cos(pitch) * glm::sin(yaw),
            glm::sin(pitch),
            glm::cos(pitch) * glm::cos(yaw)
    );

    vec3 right(
            sin(yaw - 1.5707f),
            0,
            cos(yaw - 1.5707f)
    );

    vec3 up = cross(right, direction);

    mat4 modelMatrix(1.0f);

    vec2 viewportSize = renderer->getSize();
    float aspectRatio = (float) viewportSize.x / viewportSize.y;

    mat4 projectionMatrix = perspective(radians(FOV), aspectRatio, NEAR_PLANE, FAR_PLANE);

    mat4 viewMatrix = lookAt(
            position,
            position + direction,
            up
    );

    mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
    frustum.calculate(mvpMatrix);
    return mvpMatrix;
}

Frustum Camera::getFrustum() {
    return frustum;
}

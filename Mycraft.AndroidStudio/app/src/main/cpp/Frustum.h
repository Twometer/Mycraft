//
// Created by twome on 20/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_FRUSTUM_H
#define MYCRAFT_ANDROIDSTUDIO_FRUSTUM_H


#include "glm/glm.hpp"

class Frustum {
public:
    void calculate(glm::mat4 mvpMatrix);

    bool cubeInFrustum(float x, float y, float z, float size);
};


#endif //MYCRAFT_ANDROIDSTUDIO_FRUSTUM_H

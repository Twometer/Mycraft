//
// Created by twome on 22/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_AABB_H
#define MYCRAFT_ANDROIDSTUDIO_AABB_H

#include "../glm/glm.hpp"

class AABB {
public:
    glm::vec3 p0;
    glm::vec3 p1;

    AABB(glm::vec3 p0, glm::vec3 p1);

    AABB expand(double x, double y, double z);

    AABB grow(double x, double y, double z);

    double clipXCollide(AABB c, double xa);

    double clipYCollide(AABB c, double ya);

    double clipZCollide(AABB c, double za);

    bool intersects(AABB c);

    void move(double x, double y, double z);
};


#endif //MYCRAFT_ANDROIDSTUDIO_AABB_H

//
// Created by twome on 22/06/2018.
//

#include "AABB.h"

using namespace glm;

AABB::AABB(vec3 p0, vec3 p1)
{
    this->p0 = p0;
    this->p1 = p1;
}

AABB AABB::expand(double x, double y, double z) {
    vec3 p0_ = p0;
    vec3 p1_ = p1;
    if (x < 0) p0_.x += x;
    if (x > 0) p1_.x += x;
    if (y < 0) p0_.y += y;
    if (y > 0) p1_.y += y;
    if (z < 0) p0_.z += z;
    if (z > 0) p1_.z += z;
    return AABB(p0_, p1_);
}

AABB AABB::grow(double x, double y, double z) {
    vec3 p0_ = p0 - vec3(x, y, z);
    vec3 p1_ = p1 + vec3(x, y, z);
    return AABB(p0_, p1_);
}

double AABB::clipXCollide(AABB c, double xa) {
    if (c.p1.y <= p0.y || c.p0.y >= p1.y) return xa;
    if (c.p1.z <= p0.z || c.p0.z >= p1.z) return xa;
    if (xa > 0 && c.p1.x <= p0.x) {
        double max = p0.x - c.p1.x;
        if (max < xa) xa = max;
    }
    if (xa < 0 && c.p0.x >= p1.x) {
        double max = p1.x - c.p0.x;
        if (max > xa) xa = max;
    }
    return xa;
}

double AABB::clipYCollide(AABB c, double ya) {
    if (c.p1.x <= p0.x || c.p0.x >= p1.x) return ya;
    if (c.p1.z <= p0.z || c.p0.z >= p1.z) return ya;
    if (ya > 0 && c.p1.y <= p0.y) {
        double max = p0.y - c.p1.y;
        if (max < ya) ya = max;
    }
    if (ya < 0 && c.p0.y >= p1.y) {
        double max = p1.y - c.p0.y;
        if (max > ya) ya = max;
    }
    return ya;
}

double AABB::clipZCollide(AABB c, double za) {
    if (c.p1.x <= p0.x || c.p0.x >= p1.x) return za;
    if (c.p1.y <= p0.y || c.p0.y >= p1.y) return za;
    if (za > 0 && c.p1.z <= p0.z) {
        double max = p0.z - c.p1.z;
        if (max < za) za = max;
    }
    if (za < 0 && c.p0.z >= p1.z) {
        double max = p1.z - c.p0.z;
        if (max > za) za = max;
    }
    return za;
}

bool AABB::intersects(AABB c) {
    return c.p1.x > p0.x && c.p0.x < p1.x && c.p1.y > p0.y && p0.y < p1.y && c.p1.z > p0.z && c.p0.z < p1.z;
}

void AABB::move(double x, double y, double z) {
    vec3 v = vec3(x, y, z);
    p0 += v;
    p1 += v;
}
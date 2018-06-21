//
// Created by twome on 16/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_RENDERER_H
#define MYCRAFT_ANDROIDSTUDIO_RENDERER_H

#include "Loader.h"
#include "glm/vec2.hpp"
#include "world/World.h"
#include "Camera.h"
#include "net/PacketHandler.h"

class Camera;
class Renderer {
public:
    void initialize(Loader loader);

    void resize(int width, int height);

    void drawFrame();

    glm::vec2 getSize();

    void rotatePlayer(float dx, float dy);

    void onPadTouch(bool down, float x, float y);

    PacketHandler* getPacketHandler();

    static World* getWorld();

    static Player* getPlayer();

    static bool isCubeInFrustum(float x, float y, float z, float size);
};


#endif //MYCRAFT_ANDROIDSTUDIO_RENDERER_H

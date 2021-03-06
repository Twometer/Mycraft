//
// Created by twome on 16/06/2018.
//

#include "Renderer.h"
#include "gui/GuiRenderer.h"
#include "glm/gtc/matrix_transform.hpp"
#include "render/AsyncSectionQueue.h"
#include "block/BlockRegistry.h"
#include "gui/ControlPad.h"
#include "glm/gtc/random.hpp"
#include "net/PacketHandler.h"
#include "TickEngine.h"
#include "gui/FontRenderer.h"
#include "util/jtime.h"
#include "Logger.h"
#include <sstream>

Player *player;
Camera *camera;
World *world;
ControlPad *controlPad;
PacketHandler *packetHandler;
TickEngine *tickEngine;

int viewport_width;
int viewport_height;

GLuint terrainTexture;
GLuint fontTexture;
GLuint crosshairTexture;

GLuint guiShader;
GLint guiShader_loc_projectionMatrix;

GLuint texturedGuiShader;
GLint texturedGuiShader_loc_projectionMatrix;

GLuint terrainShader;
GLint terrainShader_loc_mvpMatrix;

GLuint terrainVao;

glm::mat4 ortho_projection;

int frames;
int framesPerSecond;
long lastReset;

bool initialized = false;

// TODO:
// - Add texture loader to load texturepacks from ZIP file
// - Add GUI for connecting etc.
// - Add textures for the buttons

void Renderer::initialize(Loader loader) {
    glClearColor(0.537f, 0.808f, 0.98f, 1.0f);
    glViewport(0, 0, viewport_width, viewport_height);

    if (!initialized) {
        controlPad = new ControlPad();
        player = new Player();
        camera = new Camera(player, this);
        world = new World();
        packetHandler = new PacketHandler();
        tickEngine = new TickEngine();

        AsyncSectionQueue::initialize();
        BlockRegistry::initialize();
        initialized = true;
    } else {
        world->reload();
    }

    terrainTexture = loader.loadTexture("atlas_blocks.png", Interpolation::NEAREST);
    fontTexture = loader.loadTexture("ascii.png", Interpolation::NEAREST);
    crosshairTexture = loader.loadTexture("crosshair.png", Interpolation::NEAREST);

    guiShader = loader.loadShader("gui");
    guiShader_loc_projectionMatrix = glGetUniformLocation(guiShader, "projectionMatrix");

    texturedGuiShader = loader.loadShader("texturedgui");
    texturedGuiShader_loc_projectionMatrix = glGetUniformLocation(texturedGuiShader,
                                                                  "projectionMatrix");

    terrainShader = loader.loadShader("terrain");
    terrainShader_loc_mvpMatrix = glGetUniformLocation(terrainShader, "mvpMatrix");

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);

    glGenVertexArrays(1, &terrainVao);
}

void Renderer::resize(int width, int height) {
    viewport_width = width;
    viewport_height = height;
    glViewport(0, 0, viewport_width, viewport_height);
    ortho_projection = glm::ortho(-1.0f, 1.0f, 1.0f, -1.0f);
    controlPad->build(viewport_width, viewport_height);
}

void Renderer::drawFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glUseProgram(terrainShader);
    glm::mat4 mvp = camera->compute();
    glUniformMatrix4fv(terrainShader_loc_mvpMatrix, 1, GL_FALSE, &mvp[0][0]);

    glBindVertexArray(terrainVao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, terrainTexture);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    world->render(RENDERPASS_SOLID);

    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glUseProgram(guiShader);
    glUniformMatrix4fv(guiShader_loc_projectionMatrix, 1, GL_FALSE, &ortho_projection[0][0]);

    GuiRenderer *guiRenderer = new GuiRenderer(2);
    controlPad->render(guiRenderer);
    guiRenderer->drawRectNormalized(-0.01f, -0.01f, 0.01f, 0.01f, COLORDATA(0, 0, 0, 0), getSize());
    guiRenderer->buildAndRender();

    glBindTexture(GL_TEXTURE_2D, fontTexture);
    glUseProgram(texturedGuiShader);
    glUniformMatrix4fv(texturedGuiShader_loc_projectionMatrix, 1, GL_FALSE,
                       &ortho_projection[0][0]);

    delete guiRenderer;

    FontRenderer renderer;
    renderer.drawStringWithShadow(-0.9f, 0.9f, "Mycraft v0.6.0-beta", COLORDATA());
    renderer.drawStringWithShadow(-0.9f, 0.8f, (std::to_string(framesPerSecond) + " fps").c_str(),
                                  COLORDATA());
    renderer.finish();

    long curTime = static_cast<long>(time_util::get_time_nanos());
    frames++;
    if (curTime - lastReset > 1000000000) {
        lastReset = curTime;
        framesPerSecond = frames;
        frames = 0;
    }

    handleTimer();
}

glm::vec2 Renderer::getSize() {
    return glm::vec2(viewport_width, viewport_height);
}

void Renderer::rotatePlayer(float dx, float dy) {
    player->rotate(-dx * (360.f / viewport_width), -dy * (180.f / viewport_height));
    glm::vec2 newRot = player->getRotation();
}

void Renderer::onPadTouch(bool down, float x, float y) {
    controlPad->handleTouch(down, x, y);
}

void Renderer::onTouch(bool down, float x, float y) {
    if (!down)
        LOGD("Placing a block now"); // TODO implement block placing/breaking
}

void Renderer::handleTimer() {
    tickEngine->update();
    for (int i = 0; i < tickEngine->ticks; i++) {
        player->tick(controlPad);
    }
}

World *Renderer::getWorld() {
    return world;
}

bool Renderer::isCubeInFrustum(float x, float y, float z, float size) {
    return camera->getFrustum().cubeInFrustum(x, y, z, size);
}

Player *Renderer::getPlayer() {
    return player;
}

PacketHandler *Renderer::getPacketHandler() {
    return packetHandler;
}

TickEngine *Renderer::getTickEngine() {
    return tickEngine;
}



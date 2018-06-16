//
// Created by twome on 16/06/2018.
//

#include "Renderer.h"
#include "Camera.h"
#include "Logger.h"

Player *player;
Camera *camera;

int viewport_width;
int viewport_height;

GLuint terrainTexture;

GLuint guiShader;
GLuint terrainShader;
GLint terrainShader_loc_mvpMatrix;

GLuint terrainVao;

void Renderer::initialize(Loader loader) {
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
    glViewport(0, 0, viewport_width, viewport_height);

    player = new Player();
    camera = new Camera(player, this);

    terrainTexture = loader.loadTexture("atlas_blocks.png", Interpolation::NEAREST);

    guiShader = loader.loadShader("gui");

    terrainShader = loader.loadShader("terrain");
    terrainShader_loc_mvpMatrix = glGetUniformLocation(terrainShader, "mvpMatrix");

    glGenVertexArrays(1, &terrainVao);
}

void Renderer::resize(int width, int height) {
    viewport_width = width;
    viewport_height = height;
}

void Renderer::drawFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(terrainShader);
    glm::mat4 mvp = camera->compute();
    glUniformMatrix4fv(terrainShader_loc_mvpMatrix, 1, GL_FALSE, &mvp[0][0]);

    glBindVertexArray(terrainVao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, terrainTexture);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // TODO Render world

    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

}

glm::vec2 Renderer::getSize() {
    return glm::vec2(viewport_width, viewport_height);
}

void Renderer::rotatePlayer(float dx, float dy) {
    player->rotate(dx * (360.f / viewport_width), dy * (180.f / viewport_height));
    glm::vec2 newRot = player->getRotation();
    LOGD("Changed rotation to %f/%f\n", newRot.x, newRot.y);
}

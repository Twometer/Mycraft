//
// Created by twome on 16/06/2018.
//

#include "Renderer.h"

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
    glUniformMatrix4fv(terrainShader_loc_mvpMatrix, 1, GL_FALSE, nullptr); // TODO

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

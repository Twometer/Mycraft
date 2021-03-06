//
// Created by twome on 15/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_LOADER_H
#define MYCRAFT_ANDROIDSTUDIO_LOADER_H

#include <GLES3/gl3.h>
#include <string>

enum Interpolation {
    SMOOTH,
    NEAREST
};

class Loader {
    std::string basePath;
public:
    GLuint loadShader(std::string shaderName);
    GLuint loadShader(std::string vertPath, std::string fragPath);
    GLuint loadTexture(std::string imageName, Interpolation interpolation);
    void setBasePath(std::string basePath);
};


#endif //MYCRAFT_ANDROIDSTUDIO_LOADER_H

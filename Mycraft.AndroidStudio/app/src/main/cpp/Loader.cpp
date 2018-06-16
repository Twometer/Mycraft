//
// Created by twome on 15/06/2018.
//
#include "Loader.h"
#include <android/log.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "lodepng/lodepng.h"

#define  LOG_TAG    "MyCraft_Native"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

using namespace std;

void checkShader(GLuint shader) {
    GLint Result = GL_FALSE;
    int InfoLogLength;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(shader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        LOGD("%s\n", &VertexShaderErrorMessage[0]);
    }
}

const char *readFile(std::string path) {
    string *contents = NULL;
    ifstream fileStream(path.c_str(), ios::in);

    if (fileStream.is_open()) {
        stringstream temp;
        temp << fileStream.rdbuf();
        contents = new string(temp.str());
        fileStream.close();
    }
    if (contents == NULL) {
        LOGD("Failed to read file: %s\n", strerror(errno));
        return NULL;
    }
    return contents->c_str();
}

GLuint Loader::loadShader(std::string shaderName) {
    LOGD("Loading shader %s\n", shaderName.c_str());
    return loadShader(shaderName + "_v.glsl", shaderName + "_f.glsl");
}

GLuint Loader::loadShader(std::string vertPath, std::string fragPath) {
    std::string shaderBase = basePath + "/shaders/";
    const char *vert = readFile(shaderBase + vertPath);
    const char *frag = readFile(shaderBase + fragPath);

    if (vert == NULL || frag == NULL) {
        LOGD("Error: Failed to load shaders\n");
        return 0;
    }


    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShaderId, 1, &vert, NULL);
    glCompileShader(vertexShaderId);

    checkShader(vertexShaderId);

    glShaderSource(fragmentShaderId, 1, &frag, NULL);
    glCompileShader(fragmentShaderId);

    checkShader(fragmentShaderId);

    GLuint programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);

    glDetachShader(programId, vertexShaderId);
    glDetachShader(programId, fragmentShaderId);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return programId;
}

void Loader::setBasePath(std::string basePath) {
    this->basePath = basePath;
}

GLuint Loader::loadTexture(std::string imageName, Interpolation interpolation) {
    string imagePath = basePath + "/textures/" + imageName;
    vector<unsigned char> image = vector<unsigned char>();
    unsigned width, height;
    unsigned error = lodepng::decode(image, width, height, imagePath.c_str());
    if (error)
        LOGD("Failed to decode image %s: %s\n", imageName.c_str(), lodepng_error_text(error));

    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 &image.front());

    GLint filter = interpolation == Interpolation::NEAREST ? GL_NEAREST : GL_LINEAR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureId;
}

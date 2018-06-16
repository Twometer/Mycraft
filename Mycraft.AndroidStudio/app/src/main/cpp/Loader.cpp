//
// Created by twome on 15/06/2018.
//
#include "Loader.h"
#include <android/log.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

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
    string* contents;
    ifstream fileStream(path.c_str(), ios::in);
    if (fileStream.is_open()) {
        stringstream temp;
        temp << fileStream.rdbuf();
        contents = new string(temp.str());
        fileStream.close();
    }
    return contents->c_str();
}

GLuint Loader::loadShader(std::string shaderName) {
    return loadShader(shaderName + "_v.glsl", shaderName + "_f.glsl");
}

GLuint Loader::loadShader(std::string vertPath, std::string fragPath) {
    std::string shaderBase = basePath + "/shaders/";
    const char *vert = readFile(shaderBase + vertPath);
    const char *frag = readFile(shaderBase + fragPath);

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
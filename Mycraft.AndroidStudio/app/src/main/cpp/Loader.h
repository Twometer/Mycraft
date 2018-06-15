//
// Created by twome on 15/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_LOADER_H
#define MYCRAFT_ANDROIDSTUDIO_LOADER_H


#include <GLES3/gl3.h>

class Loader {
public:
    GLuint loadShader(const char* vert, const char* frag);

};


#endif //MYCRAFT_ANDROIDSTUDIO_LOADER_H

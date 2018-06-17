//
// Created by twome on 17/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_VERTICES_H
#define MYCRAFT_ANDROIDSTUDIO_VERTICES_H

#include <GLES3/gl3.h>

static const GLfloat vertices_negative_x[] = {
        0.0f, 0.0f, 0.0f, // Neg x
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, // Neg x
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f
};

static const GLfloat tvertices_negative_x[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
};

static const GLfloat vertices_negative_y[] = {
        1.0f, 0.0f, 1.0f, // Neg y
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, // Neg y
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,
};

static const GLfloat tvertices_negative_y[] = {
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
};

static const GLfloat vertices_negative_z[] = {
        1.0f, 1.0f, 0.0f, // Neg z
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,  // Neg z
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
};

static const GLfloat tvertices_negative_z[] = {
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f
};

static const GLfloat vertices_positive_x[] = {
        1.0f, 0.0f, 0.0f, // Pos x
        1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, // Pos x
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
};

static const GLfloat tvertices_positive_x[] = {
        1.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
};

static const GLfloat vertices_positive_y[] = {
        1.0f, 1.0f, 1.0f, // Pos y
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, // Posy
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
};

static const GLfloat tvertices_positive_y[] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
};


static const GLfloat vertices_positive_z[] = {
        0.0f, 1.0f, 1.0f, // Pos z
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, // Pos z
        0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f
};

static const GLfloat tvertices_positive_z[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f
};

static const GLfloat plantvertices_a[] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f
};

static const GLfloat tplantvertices_a[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
};

static const GLfloat plantvertices_b[] = {
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f
};

static const GLfloat tplantvertices_b[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
};

static const GLfloat plantvertices_c[] = {
        1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f,
};

static const GLfloat tplantvertices_c[] = {
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f
};

static const GLfloat plantvertices_d[] = {
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
};

static const GLfloat tplantvertices_d[] = {
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f
};

#endif //MYCRAFT_ANDROIDSTUDIO_VERTICES_H

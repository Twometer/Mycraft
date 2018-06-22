//
// Created by twome on 22/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_FONTRENDERER_H
#define MYCRAFT_ANDROIDSTUDIO_FONTRENDERER_H


#include <string>
#include "GuiRenderer.h"

class FontRenderer {
private:
    GuiRenderer guiRenderer = GuiRenderer(2);
    static unsigned char* fontWidths;
public:
    FontRenderer();

    void drawString(GLfloat x, GLfloat y, std::string string, COLORDATA colordata);

    void drawStringWithShadow(GLfloat x, GLfloat y, const char *string, COLORDATA colordata);

    void finish();

    static void setFontWidths(unsigned char* fontWidths);
};


#endif //MYCRAFT_ANDROIDSTUDIO_FONTRENDERER_H

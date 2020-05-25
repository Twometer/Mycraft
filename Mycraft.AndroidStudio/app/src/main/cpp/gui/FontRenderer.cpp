//
// Created by twome on 22/06/2018.
//

#include "FontRenderer.h"
#include "../glm/vec2.hpp"
#include "../Renderer.h"
#include "../Logger.h"

unsigned char *FontRenderer::fontWidths;

FontRenderer::FontRenderer() {
}


unsigned long upper_power_of_two(unsigned long v) {
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

float scaleNopow(float val) {
    return Renderer::getSize().x / (720.f / val);
}

float scale(float val) {
    return upper_power_of_two(static_cast<unsigned long>(scaleNopow(val)));
}

void FontRenderer::drawString(GLfloat x, GLfloat y, std::string string, COLORDATA colordata) {
    float idx = 0;

    std::string page = "\u00c0\u00c1\u00c2\u00c8\u00ca\u00cb\u00cd\u00d3\u00d4\u00d5\u00da\u00df\u00e3\u00f5\u011f\u0130\u0131\u0152\u0153\u015e\u015f\u0174\u0175\u017e\u0207 !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\u00c7\u00fc\u00e9\u00e2\u00e4\u00e0\u00e5\u00e7\u00ea\u00eb\u00e8\u00ef\u00ee\u00ec\u00c4\u00c5\u00c9\u00e6\u00c6\u00f4\u00f6\u00f2\u00fb\u00f9\u00ff\u00d6\u00dc\u00f8\u00a3\u00d8\u00d7\u0192\u00e1\u00ed\u00f3\u00fa\u00f1\u00d1\u00aa\u00ba\u00bf\u00ae\u00ac\u00bd\u00bc\u00a1\u00ab\u00bb\u2591\u2592\u2593\u2502\u2524\u2561\u2562\u2556\u2555\u2563\u2551\u2557\u255d\u255c\u255b\u2510\u2514\u2534\u252c\u251c\u2500\u253c\u255e\u255f\u255a\u2554\u2569\u2566\u2560\u2550\u256c\u2567\u2568\u2564\u2565\u2559\u2558\u2552\u2553\u256b\u256a\u2518\u250c\u2588\u2584\u258c\u2590\u2580\u03b1\u03b2\u0393\u03c0\u03a3\u03c3\u03bc\u03c4\u03a6\u0398\u03a9\u03b4\u221e\u2205\u2208\u2229\u2261\u00b1\u2265\u2264\u2320\u2321\u00f7\u2248\u00b0\u2219\u00b7\u221a\u207f\u00b2\u25a0";
    float sz = scale(16);
    for (std::string::iterator it = string.begin(); it != string.end(); ++it) {
        char chr = *it;
        int i = (int) chr;
        int texY = i >> 4;
        int texX = i % 16;
        float texmod = 8.f / 128.f;
        float width = sz / Renderer::getSize().x;
        float height = sz / Renderer::getSize().y;
        guiRenderer.drawRect(x + idx, y, width, height, colordata,
                             TEXDATA(texX * texmod, texY * texmod, texX * texmod + texmod,
                                     texY * texmod + texmod));
        idx += (scale(fontWidths[i] * 2) + scaleNopow(5)) / Renderer::getSize().x;
    }
}

void
FontRenderer::drawStringWithShadow(GLfloat x, GLfloat y, const char *string, COLORDATA colordata) {
    glm::vec2 size = Renderer::getSize();
    float sz = scale(2);

    drawString(x + (sz / size.x), y - (sz / size.y), string, COLORDATA(0, 0, 0, 255));
    drawString(x, y, string, colordata);
}

void FontRenderer::finish() {
    guiRenderer.buildAndRender();
}

void FontRenderer::setFontWidths(unsigned char *fontWidths) {
    FontRenderer::fontWidths = new unsigned char[256];
    memcpy(FontRenderer::fontWidths, fontWidths, 256);
}

FontRenderer::~FontRenderer() {

}


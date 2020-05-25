#version 300 es
precision mediump float;

in vec2 textureCoords;
out vec4 out_Colour;
uniform sampler2D colourTexture;

void main(void) {
    out_Colour = texture(colourTexture, textureCoords);
}
#version 300 es
precision mediump float;

in vec4 fragmentColor;
out vec4 out_Colour;

void main(void) {
    out_Colour = fragmentColor;
}
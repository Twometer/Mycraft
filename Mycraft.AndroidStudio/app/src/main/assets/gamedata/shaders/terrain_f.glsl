#version 300 es
precision mediump float;

in float fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D texSampler;

void main(void) {
    color = texture(texSampler, fragmentUV) * fragmentColor;
}
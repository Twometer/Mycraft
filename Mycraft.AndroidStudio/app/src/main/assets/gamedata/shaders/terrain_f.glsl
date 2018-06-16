#version 300 es
precision mediump float;

in vec3 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D texSampler;

void main(void) {
    color = texture(texSampler, fragmentUV) * vec4(fragmentColor, 1.0);
}
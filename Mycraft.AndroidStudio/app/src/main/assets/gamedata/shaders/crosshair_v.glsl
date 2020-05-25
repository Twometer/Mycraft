#version 300 es

layout(location = 0) in vec2 position;

out vec2 textureCoords;

uniform mat4 projectionMatrix;
uniform vec2 offset;

void main(void) {
    gl_Position = projectionMatrix * vec4(position + offset - vec2(8, 8), 0.0, 1.0);
    textureCoords = position * 0.0625;
}
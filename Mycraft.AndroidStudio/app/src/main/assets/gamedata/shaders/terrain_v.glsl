#version 300 es

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in float vertexColor;
layout(location = 2) in vec2 vertexUV;

out float fragmentColor;
out vec2 fragmentUV;

uniform mat4 mvpMatrix;

void main(void) {
    gl_Position = mvpMatrix * vec4(vertexPosition_modelspace, 1.0);
    fragmentColor = vertexColor;
    fragmentUV = vertexUV;
}
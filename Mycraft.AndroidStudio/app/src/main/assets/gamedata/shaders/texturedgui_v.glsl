#version 300 es

layout(location = 0) in vec2 position;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 vertexUV;

out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 projectionMatrix;

void main(void) {
    gl_Position = vec4(position, 0.0, 1.0);
    fragmentColor = vertexColor;
	fragmentUV = vertexUV;
}
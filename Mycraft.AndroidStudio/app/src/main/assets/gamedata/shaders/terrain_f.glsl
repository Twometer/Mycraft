#version 300 es
precision mediump float;

in float fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D texSampler;

void main(void) {
    vec4 textureColor = texture(texSampler, fragmentUV);
    if(textureColor.a < 0.1)
        discard;
    color = textureColor * fragmentColor;
}
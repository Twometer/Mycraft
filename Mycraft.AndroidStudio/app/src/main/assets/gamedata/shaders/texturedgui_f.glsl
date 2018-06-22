#version 300 es
precision mediump float;

in vec4 fragmentColor;
in vec2 fragmentUV;
out vec4 out_Colour;

uniform sampler2D texSampler;

void main(void) {
	vec4 textureColor = texture(texSampler, fragmentUV);
    if(textureColor.a == 0.0)
        discard;
    out_Colour = textureColor * fragmentColor;
}
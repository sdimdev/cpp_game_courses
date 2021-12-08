#version 330 core
in vec2 oPos;
uniform sampler2D uTexture;
in vec2 oTexCoord;
out vec4 color;
void main()
{
color = (0.4 + texture(uTexture, oTexCoord)) * oTexCoord.x;
};
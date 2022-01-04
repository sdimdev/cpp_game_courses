#version 330 core
layout (location = 0) in vec4 color;
layout (location = 1) in vec2 velocity;
layout (location = 2) in vec2 position;

out vec2 oPos;
uniform float time;
void main()
{
oPos = velocity + velocity * time;
gl_Position = vec4(oPos.x, oPos.y, 1.0, 1.0);
//gl_Position = vec2(oPos.x, oPos.y);
//oTexCoord = texCoord;
};
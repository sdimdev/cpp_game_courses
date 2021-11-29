#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec4 color;
out vec2 oPos;
out vec4 oColor;
uniform vec2 screenSize;
void main()
{
oPos = position / screenSize * 2.0 - vec2(1.0);
gl_Position = vec4(oPos.x, oPos.y, 1.0, 1.0);
oColor = color;
};
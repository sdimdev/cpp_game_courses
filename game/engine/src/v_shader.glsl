#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
out vec2 oPos;
out vec2 oTexCoord;
uniform vec2 screenSize;
uniform mat4 transform;
void main()
{
oPos = vec2(position.x, position.y) / screenSize * 2.0 - vec2(1.0);
gl_Position = transform * vec4(oPos.x, oPos.y, 1.0, 1.0);
oTexCoord = texCoord;
};
#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;
out vec2 oPos;
out vec2 oTexCoord;
uniform vec2 screenSize;
uniform mat3 transform;
void main()
{
oPos = (transform * vec3(position.x, position.y, 1.0)).xy / vec2(640, 480) * 2.0 - vec2(1.0);
gl_Position = vec4(vec3(oPos.x, oPos.y, 1.0), 1.0);
//gl_Position = vec2(oPos.x, oPos.y);
oTexCoord = texCoord;
};
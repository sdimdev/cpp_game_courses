#version 330 core
in vec2 oPos;
uniform sampler2D uTexture;
//uniform vec2 textureSize;
in vec2 oTexCoord;
//vec2 textur;
out vec4 color;
void main()
{
//color = vec4(oPos.x, oPos.y, (oPos.x+oPos.y)/2, 1.0);
//textur = vec2(oTexCoord.x * textureSize.x, oTexCoord.y * textureSize.y);
color = texture(uTexture, oTexCoord);
};

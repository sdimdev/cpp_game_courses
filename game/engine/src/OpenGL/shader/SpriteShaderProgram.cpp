//
// Created by dzmitry on 04.12.2021.
//

#include "SpriteShaderProgram.hpp"
#include <utils/GLUtils.cpp>
#include <GL/glew.h>
#include <iostream>
#include <unistd.h>
#include <utils/FileUtils.cpp>
#include <gtc/type_ptr.hpp>


SpriteShaderProgram::SpriteShaderProgram(
        std::string_view vpath,
        std::string_view fpath
) : GLProgram(loadFromFile(vpath), loadFromFile(fpath))
{


}

SpriteShaderProgram::~SpriteShaderProgram() = default;
//задаем униформу
/*_pimpl->screenSizeUniform = glGetUniformLocation(_pimpl->program, "screenSize");
_pimpl->transformUniform = glGetUniformLocation(_pimpl->program, "transform");
_pimpl->texturesUniform = glGetUniformLocation(_pimpl->program, "uTexture");
_pimpl->textureSizeUniform = glGetUniformLocation(_pimpl->program, "textureSize");*/
//bind texture
/*   glActiveTexture(GL_TEXTURE0);
   glUniform1i(textureUniform(), 0);
   //glUniform2i(_pimpl->textureSizeUniform, _pimpl->tl.width, _pimpl->tl.height);
   glBindTexture(GL_TEXTURE_2D, texture);
*/

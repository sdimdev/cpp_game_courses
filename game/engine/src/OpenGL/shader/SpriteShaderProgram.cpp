//
// Created by dzmitry on 04.12.2021.
//

#include "SpriteShaderProgram.hpp"
#include <utils/FileUtils.cpp>


SpriteShaderProgram::SpriteShaderProgram(
        std::string_view vpath,
        std::string_view fpath
) : GLProgram(loadFromFile(vpath), loadFromFile(fpath))
{


}

void SpriteShaderProgram::activate()
{
    GLProgram::activate();
}

SpriteShaderProgram::~SpriteShaderProgram() = default;

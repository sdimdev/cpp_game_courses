//
// Created by dzmitry on 04.12.2021.
//

#ifndef GAME_SPRITESHADERPROGRAM_HPP
#define GAME_SPRITESHADERPROGRAM_HPP


#include <memory>
#include <entity/TransformData.hpp>
#include "OpenGL/shader/GLProgram.hpp"

class SpriteShaderProgram: public GLProgram
{
public:
    explicit SpriteShaderProgram(std::string_view vpath,
                                 std::string_view fpath);
    void activate() override;
    ~SpriteShaderProgram();
};

#endif //GAME_SPRITESHADERPROGRAM_HPP

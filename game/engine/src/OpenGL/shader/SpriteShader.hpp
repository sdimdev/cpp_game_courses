//
// Created by dzmitry on 04.12.2021.
//

#ifndef GAME_SPRITESHADER_HPP
#define GAME_SPRITESHADER_HPP


#include <memory>
#include "ShaderProgram.hpp"

class SpriteShader: public ShaderProgram
{
public:
    explicit SpriteShader();
    void loadProgram() override;
    ~SpriteShader();
private:
    struct Pimpl;
    std::unique_ptr<Pimpl> _pimpl;
};


#endif //GAME_SPRITESHADER_HPP

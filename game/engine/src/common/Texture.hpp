//
// Created by dzmitry on 07.12.2021.
//

#ifndef GAME_TEXTURE_HPP
#define GAME_TEXTURE_HPP


#include "ITexture.hpp"

class Texture : public ITexture
{
public:
    explicit Texture(glm::vec2 size);
    ~Texture();
protected:
    glm::vec2 size;
};

#endif //GAME_TEXTURE_HPP

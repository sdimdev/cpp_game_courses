//
// Created by dzmitry on 07.12.2021.
//

#ifndef GAME_ITEXTURE_HPP
#define GAME_ITEXTURE_HPP

class ITexture
{
public:
    ~ITexture() = default;

    ITexture() = default;

    virtual glm::vec2 getSize() = 0;
};

#endif //GAME_ITEXTURE_HPP

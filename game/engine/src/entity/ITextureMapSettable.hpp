//
// Created by dzmitry on 06.01.2022.
//

#ifndef GAME_ITEXTUREMAPSETTABLE_HPP
#define GAME_ITEXTUREMAPSETTABLE_HPP

#include <vec2.hpp>

class ITextureMapSettable
{
public:
    virtual void setTexturePoint1(glm::vec2 point) = 0;

    virtual void setTexturePoint2(glm::vec2 point) = 0;

    virtual ~ITextureMapSettable()
    {};
};

#endif //GAME_ITEXTUREMAPSETTABLE_HPP

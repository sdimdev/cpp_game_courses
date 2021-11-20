//
// Created by dzmitry on 19.11.2021.
//

#ifndef GAME_IPOINT3SHADER_HPP
#define GAME_IPOINT3SHADER_HPP


#include <domain/Point3f.hpp>

class IPoint3Shader
{
public:
    virtual Point3f apply(Point3f p) = 0;
};


#endif //GAME_IPOINT3SHADER_HPP

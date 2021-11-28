//
// Created by dzmitry on 19.11.2021.
//

#ifndef GAME_IPIXELSHADER_HPP
#define GAME_IPIXELSHADER_HPP


#include <entity/Point3f.hpp>
#include <entity/RGBAColor.hpp>

class IPixelShader
{
public:
    //todo change to Point2d
    virtual RGBAColor apply(Point3f p, RGBAColor c) = 0;
};


#endif //GAME_IPIXELSHADER_HPP

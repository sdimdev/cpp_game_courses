//
// Created by dzmitry on 21.11.2021.
//

#ifndef GAME_LENSPIXELSHADER_HPP
#define GAME_LENSPIXELSHADER_HPP


#include <domain/Point3f.hpp>
#include <domain/RGBAColor.hpp>
#include "IPixelShader.hpp"

class LensPixelShader : public IPixelShader
{
public:
    explicit LensPixelShader(Point3f point, int r);

    RGBAColor apply(Point3f p, RGBAColor c) override;

    void moveToPoint(Point3f point);

    ~LensPixelShader();

    Point3f getPoint();

private:
    int r;
    int rQuad;
    Point3f lensPoint;
};


#endif //GAME_LENSPIXELSHADER_HPP

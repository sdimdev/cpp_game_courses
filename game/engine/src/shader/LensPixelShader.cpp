//
// Created by dzmitry on 21.11.2021.
//

#include "LensPixelShader.hpp"
#include <cmath>

RGBAColor LensPixelShader::apply(Point3f point, RGBAColor color)
{
    if (r == 0)
    {
        return color;
    }
    int dx = point.getX() - this->lensPoint.getX();
    int dy = point.getY() - this->lensPoint.getY();
    if (dy < r && dy > -r || dx < r && dx > -r)
    { //in a square
        Point3f direction = point - lensPoint;
        float distance = direction.abs();
        if (distance < r)
        {
            //todo too bad
            float koef = 1 - sqrt(distance / r);
            int r = 255 * koef*1.5;
            int g = color.getGreen() - 255 * koef;
            int b = 0;//color.getBlue() + 255 * koef;
            if (r > 255) r = 255;
            if (r < 0) r = 0;
            if (g > 255) g = 255;
            if (g < 0) g = 0;
            if (b > 255) b = 255;
            if (b < 0) b = 0;
            return RGBAColor(r, g, b, color.getAlpha());
        }
    }
    return color;
}

LensPixelShader::LensPixelShader(Point3f point, int r)
{
    this->r = r;
    this->rQuad = r * r;
    this->lensPoint = point;
}

void LensPixelShader::moveToPoint(Point3f point)
{
    this->lensPoint = point;
}

Point3f LensPixelShader::getPoint()
{
    return lensPoint;
}

LensPixelShader::~LensPixelShader() = default;
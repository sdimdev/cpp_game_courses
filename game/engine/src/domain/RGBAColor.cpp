//
// Created by dzmitry on 19.11.2021.
//

#include "RGBAColor.hpp"

RGBAColor::RGBAColor(int r, int g, int b, int a)
{
    this->a = a;
    this->r = r;
    this->g = g;
    this->b = b;
}

void RGBAColor::setRed(int red)
{
    this->r = red;
}

void RGBAColor::setGreen(int green)
{
    this->g = green;
}

void RGBAColor::setBlue(int blue)
{
    this->b = blue;
}

void RGBAColor::setAlpha(int alpha)
{
    this->a = alpha;
}

int RGBAColor::getRed() const
{
    return r;
}

int RGBAColor::getGreen() const
{
    return g;
}

int RGBAColor::getBlue() const
{
    return b;
}

int RGBAColor::getAlpha() const
{
    return a;
}

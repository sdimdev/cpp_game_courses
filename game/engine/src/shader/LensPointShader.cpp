//
// Created by dzmitry on 19.11.2021.
//

#include "LensPointShader.hpp"
#include <cmath>

Point3f LensPointShader::apply(Point3f point)
{
    if (r == 0)
    {
        return point;
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
            return point + (direction * (koef));
        }
    }
    return point;
}

LensPointShader::LensPointShader(Point3f point, int r)
{
    this->r = r;
    this->rQuad = r * r;
    this->lensPoint = point;
}

void LensPointShader::moveToPoint(Point3f point)
{
    this->lensPoint = point;
}

Point3f LensPointShader::getPoint()
{
    return lensPoint;
}

LensPointShader::~LensPointShader() = default;
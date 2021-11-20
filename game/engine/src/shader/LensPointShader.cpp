//
// Created by dzmitry on 19.11.2021.
//

#include "LensPointShader.hpp"
#include <cmath>

Point3f LensPointShader::apply(Point3f point)
{
    int dx = point.getX() - this->lensPoint.getX();
    int dy = point.getY() - this->lensPoint.getY();
    if (dy < r && dy > -r || dx < r && dx > -r)
    { //in a square
        Point3f direction = point - lensPoint;
        float distanceQuad = direction.sqrAbs();
        if (distanceQuad < rQuad)
        {
            direction*=std::sqrt(rQuad - distanceQuad);
            return direction;
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

//
// Created by dzmitry on 19.11.2021.
//

#include "Point2d.hpp"

Point2d::Point2d(int x, int y)
{
    this->x = x;
    this->y = y;
}

Point2d::Point2d() : Point2d(0, 0)
{}

int Point2d::getX()
{
    return x;
}

int Point2d::getY()
{
    return y;
}

void Point2d::setX(int x)
{
    this->x = x;
}

void Point2d::setY(int y)
{
    this->y = y;
}

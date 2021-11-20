//
// Created by dzmitry on 19.11.2021.
//

#include "Line3f.hpp"

Line3f::Line3f(Point3f p1, Point3f p2)
{
    this->p1 = p1;
    this->p2 = p2;
}

Point3f Line3f::getP1()
{
    return p1;
}

Line3f::Line3f() : Line3f(Point3f(), Point3f())
{}

Point3f Line3f::getP2()
{
    return p2;
}

void Line3f::setP1(Point3f p)
{
    this->p1 = p;
}

void Line3f::setP2(Point3f p)
{
    this->p2 = p;
}

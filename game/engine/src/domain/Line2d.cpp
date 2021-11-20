//
// Created by dzmitry on 19.11.2021.
//

#include "Line2d.hpp"

Line2d::Line2d(Point2d p1, Point2d p2)
{
    this->p1 = p1;
    this->p2 = p2;
}

Point2d Line2d::getP1()
{
    return p1;
}

Line2d::Line2d() : Line2d(Point2d(), Point2d())
{}

Point2d Line2d::getP2()
{
    return p2;
}

void Line2d::setP1(Point2d p)
{
    this->p1 = p;
}

void Line2d::setP2(Point2d p)
{
    this->p2 = p;
}

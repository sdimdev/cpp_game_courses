//
// Created by dzmitry on 19.11.2021.
//

#ifndef GAME_LINE2D_HPP
#define GAME_LINE2D_HPP

#include "Point2d.hpp"


class [[deprecated("use glm")]]Line2d
{
public:
    Line2d(Point2d p1, Point2d p2);

    Line2d();

    Point2d getP1();

    Point2d getP2();

    void setP1(Point2d p);

    void setP2(Point2d p);

private:
    Point2d p1;
    Point2d p2;
};


#endif //GAME_LINE2D_HPP

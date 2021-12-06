//
// Created by dzmitry on 19.11.2021.
//

#ifndef GAME_LINE2D_HPP
#define GAME_LINE2D_HPP

#include "Point3f.hpp"

class [[deprecated("use glm")]]Line3f
{
public:
    explicit Line3f(Point3f p1, Point3f p2);

    explicit Line3f();

    Point3f getP1();

    Point3f getP2();

    void setP1(Point3f p);

    void setP2(Point3f p);

private:
    Point3f p1;
    Point3f p2;
};


#endif //GAME_LINE2D_HPP

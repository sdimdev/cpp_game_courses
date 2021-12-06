//
// Created by dzmitry on 19.11.2021.
//

#ifndef GAME_POINT2D_HPP
#define GAME_POINT2D_HPP


class [[deprecated("use glm")]]Point2d
{
public:
    Point2d();

    Point2d(int x, int y);

    int getY();

    int getX();

    void setX(int x);

    void setY(int y);

private:
    int x;
    int y;
};


#endif //GAME_POINT2D_HPP

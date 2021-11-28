//
// Created by dzmitry on 19.11.2021.
//

#ifndef GAME_RGBACOLOR_HPP
#define GAME_RGBACOLOR_HPP


class RGBAColor
{

public:
    RGBAColor(int r, int g, int b, int a);

    void setRed(int red);

    void setGreen(int green);

    void setBlue(int blue);

    void setAlpha(int alpha);

    int getRed() const;

    int getGreen() const;

    int getBlue() const;

    int getAlpha() const;

private:
    int r;
    int g;
    int b;
    int a;
};


#endif //GAME_RGBACOLOR_HPP

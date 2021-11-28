//
// Created by dzmitry on 19.11.2021.
//

#ifndef GAME_LENSPOINTSHADER_HPP
#define GAME_LENSPOINTSHADER_HPP

#include "IPoint3Shader.hpp"
#include "entity/Point3f.hpp"

class LensPointShader : public IPoint3Shader
{
public:
    explicit LensPointShader(Point3f point, int r);
    Point3f apply(Point3f point) override;
    void moveToPoint(Point3f point);
    ~LensPointShader();
    Point3f getPoint();

private:
    int r;
    int rQuad;
    Point3f lensPoint;
};


#endif //GAME_LENSPOINTSHADER_HPP

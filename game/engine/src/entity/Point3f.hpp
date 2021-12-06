//
// Created by dzmitry on 19.11.2021.
//

#ifndef GAME_POINT3F_HPP
#define GAME_POINT3F_HPP

//copied from
//https://github.com/vectozavr/pseudo3DEngine/blob/master/Point3f.h
// :D


class [[deprecated("use glm")]]Point3f
{
public:
    Point3f();

    Point3f(float x, float y, float z);

    Point3f(float x, float y);

    float getX();

    float getY();

    float getZ();

    void setX(int x);

    void setY(int y);

    void setZ(int z);

    Point3f operator+(const Point3f& point3f) const;
    Point3f operator-(const Point3f& point3f) const;
    Point3f operator*(float number) const;
    Point3f operator/(float number) const;

    Point3f& operator=(const Point3f& point3f);

    Point3f& operator+=(const Point3f& point3f);
    Point3f& operator-=(const Point3f& point3f);
    Point3f& operator*=(float number);
    Point3f& operator/=(float number);

    bool operator==(const Point3f& point3f);
    bool operator!=(const Point3f& point3f);
    
    // Returns dot product
    float operator*(const Point3f& poin3D) const;
    // Returns dot product, but static
    static float dot(const Point3f& a, const Point3f& b);
    // Returns normalized vector
    Point3f normalize();
    // Returns squared vector length
    float sqrAbs();
    // Returns vector length
    float abs();

private:
    float x;
    float y;
    float z;
};


#endif //GAME_POINT3F_HPP

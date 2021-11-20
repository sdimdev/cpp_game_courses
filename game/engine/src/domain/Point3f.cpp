//
// Created by dzmitry on 19.11.2021.
//

#include "Point3f.hpp"
#include <cmath>

Point3f::Point3f(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Point3f::Point3f(float x, float y) : Point3f(x, y, 0)
{}

Point3f::Point3f() : Point3f(0, 0, 0)
{}

float Point3f::getX()
{
    return x;
}

float Point3f::getY()
{
    return y;
}

float Point3f::getZ()
{
    return z;
}

void Point3f::setX(int x)
{
    this->x = x;
}

void Point3f::setY(int y)
{
    this->y = y;
}

void Point3f::setZ(int z)
{
    this->z = z;
}

float Point3f::abs()
{
    return std::sqrt(x * x + y * y + z * z);
}


Point3f Point3f::operator+(const Point3f &point3f) const
{
    return Point3f{this->x + point3f.x, this->y + point3f.y, this->z + point3f.z};
}

Point3f Point3f::operator-(const Point3f &point3f) const
{
    return Point3f{this->x - point3f.x, this->y - point3f.y, this->z - point3f.z};
}

Point3f Point3f::operator*(float number) const
{
    return Point3f{this->x * number, this->y * number, this->z * number};
}

Point3f Point3f::operator/(float number) const
{
    return Point3f{this->x * number, this->y * number};
}

Point3f &Point3f::operator=(const Point3f &point3f)
{
    this->x = point3f.x;
    this->y = point3f.y;
    this->z = point3f.z;
    return *this;
}

Point3f &Point3f::operator+=(const Point3f &point3f)
{
    this->x += point3f.x;
    this->y += point3f.y;
    this->z += point3f.z;
    return *this;
}

Point3f &Point3f::operator-=(const Point3f &point3f)
{
    this->x -= point3f.x;
    this->y -= point3f.y;
    this->z -= point3f.z;
    return *this;
}

Point3f &Point3f::operator*=(float number)
{
    this->x *= number;
    this->y *= number;
    this->z *= number;
    return *this;
}

Point3f &Point3f::operator/=(float number)
{
    this->x /= number;
    this->y /= number;
    this->z /= number;
    return *this;
}

bool Point3f::operator==(const Point3f &point3f)
{
    return this == &point3f || (*this - point3f).sqrAbs() < 0.0000000001;
}

bool Point3f::operator!=(const Point3f &point3f)
{
    return this != &point3f && (*this - point3f).sqrAbs() > 0.0000000001;
}

float Point3f::operator*(const Point3f &point3f) const
{
    return this->x * point3f.x + this->y * point3f.y + this->z * point3f.z;
}

float Point3f::dot(const Point3f& a, const Point3f& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}


Point3f Point3f::normalize()
{
    float length = this->abs();
    return Point3f{ this->x / length, this->y / length,  this->z / length};
}

float Point3f::sqrAbs()
{
    return x * x + y * y + z * z;
}

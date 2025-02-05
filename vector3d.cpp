#include "vector3d.h"
#include "constants.h"
#include <iostream>
#include <cmath>

Vector3D::Vector3D()
    :x{0.0}, y{0.0}, z{0.0} {}

Vector3D::Vector3D(double x, double y, double z)
    :x{x}, y{y}, z{z} {}

Vector3D& Vector3D::operator+=(const Vector3D& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

Vector3D& Vector3D::operator*=(const Vector3D& rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
}
  
Vector3D& Vector3D::operator*=(const double scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3D& Vector3D::operator/=(const double scalar) {
    if (scalar == 0) {
        throw std::overflow_error("Cannot divide by 0!");
    }
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

bool almost_equal(double x, double y) {
    return std::abs(x - y) < Constants::epsilon;
}

bool operator==(const Vector3D& lhs, const Vector3D& rhs) {
    return almost_equal(lhs.x, rhs.x)
           && almost_equal(lhs.y, rhs.y)
           && almost_equal(lhs.z, rhs.z);
}

bool operator!=(const Vector3D& lhs, const Vector3D& rhs) {
    return !(lhs == rhs);
}

Vector3D operator+(Vector3D lhs, const Vector3D& rhs) {
    lhs += rhs;
    return lhs;
}

Vector3D operator-(Vector3D lhs, const Vector3D& rhs) {
    lhs -= rhs;
    return lhs;
}

Vector3D operator-(const Vector3D& rhs) {
    return Vector3D{-rhs.x, -rhs.y, -rhs.z};
}

Vector3D operator*(Vector3D lhs, const Vector3D& rhs) {
    return lhs *= rhs;
}

Vector3D operator*(Vector3D lhs, const double scalar) {
    return lhs*=scalar;
}

Vector3D operator*(const double scalar, Vector3D rhs) {
    return rhs*=scalar;
}

Vector3D operator/(Vector3D lhs, const double scalar) {
    return lhs/=scalar;
}

Vector3D pow(Vector3D v, const double n) {
    v.x = pow(v.x, n);
    v.y = pow(v.y, n);
    v.z = pow(v.z, n);
    return v;
}

double dot(const Vector3D& a, const Vector3D& b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}
  
Vector3D cross(const Vector3D& a, const Vector3D& b) {
    double i = (a.y*b.z + a.z*b.y);
    double j = (a.z*b.x + b.z*a.x);
    double k = (a.x*b.y + b.x*a.y);
    Vector3D crossed(i, j, k);
    return crossed;
}
  
double length(const Vector3D& v) {
    return sqrt((pow(v.x, 2) + pow(v.y, 2)+ pow(v.z, 2)));
}
  
Vector3D unit(const Vector3D& v) {
    double l = length(v);
    if (l == 0) {
        throw std::overflow_error("Cannot divide by 0!");
    }
    Vector3D unit_v((v.x/l), (v.y/l), (v.z/l));
    return unit_v;
}

std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
    return os << "(" << v.x << " " << v.y << " " << v.z << ")";
}

std::istream& operator>>(std::istream& is, Vector3D& v) {
    char paren;
    return is >> paren >> v.x >> v.y >> v.z >> paren;
}

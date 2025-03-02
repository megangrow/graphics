#include "sphere.h"
#include "hit.h"
#include "ray.h"
#include <cmath>

constexpr double epsilon = 1e-5;

Sphere::Sphere(const Point3D& center, double radius, const Material* material)
: center{center}, radius{radius}, material{material} {
    if (radius < 0) {
        throw std::runtime_error("Radius cannot be less than zero!");
    }
}

Hit Sphere::construct_hit(const Ray &ray, double time) const {
    // calculate the surface normal
    Point3D point = ray.at(time);
    Vector3D normal = (point - center) / radius;
    return Hit{time, point, normal, this};
}

std::optional<double> Sphere::intersect(const Ray& ray) const {
    Point3D pc = center - ray.origin;
    double a = dot(ray.direction, ray.direction);
    double b = 2 * dot(ray.direction, pc);
    double c = dot(pc, pc) - (radius * radius);
    double x = b * b - (4 * a * c);
    if (x < -epsilon) { // miss
        return std::nullopt;
    } else if (std::abs(x) < epsilon) { // single hit
        return {b / (2 * a)};
    } else if (x > epsilon) { // double hit
        return {(b - sqrt(x)) / (2 * a)};
    }
    return std::nullopt;
}

std::optional<double> Sphere::intersect_geometrically(const Ray& ray) const {
    Point3D cp = center - ray.origin;
    double tmp = dot(cp, cp);
    double q = sqrt(-dot(ray.direction, cp) + tmp);
    if (q > radius + epsilon) {
        return std::nullopt;
    }
//    if (abs(q-radius) < epsilon) {
//        // one hit
//        // distance to the point length(tmp)
//    }
//    if () {
//        t = tmp +- h if R, h pos, subtract,
//        test values of point to figure out inside/outside
//        inside = r+h, outside r-h
//    }
    // need to test for 3 cases (no, one, two hits)
    return pow(q,2); // wrong
}

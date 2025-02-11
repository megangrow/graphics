#include "sphere.h"
#include "hit.h"
#include <cmath>

constexpr double epsilon = 1e-5;

Sphere::Sphere(const Point3D& center, double radius)
: center{center}, radius{radius} {
    if (radius < 0) {
        throw std::runtime_error("Radius cannot be less than zero!");
    }
}

Hit Sphere::construct_hit(const Ray &ray, double time) const {
    // calculate the surface normal
    Point3D point = ray.at(time);
    Vector3D normal = (point - center) / radius;
    return Hit{time, point, normal};
}
//
//std::optional<double> Sphere::intersect(const Ray& ray) const {
//    Point3D oc = center - ray.origin;
//    double a = dot(ray.direction, ray.direction);
//    double b = 2.0 * dot(ray.direction, oc);
//    double c = dot(oc, oc) - radius*radius;
//    double discriminant = b*b - 4*a*c;
//    if (discriminant < epsilon) {
//        return std::nullopt;
//    }
//    double t = (b - sqrt(discriminant)) / (2*a);
//    if (discriminant < epsilon) {
//        return std::nullopt; //double
//    }
//    else if (std::abs(discriminant) < epsilon) {
//        return t; //single
//    }
//    else if (discriminant > epsilon) {
//        return t;
//    }
//    return std::nullopt;
//}

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
    if (q > radius) {
        return std::nullopt;
    }
    return pow(q,2);
}

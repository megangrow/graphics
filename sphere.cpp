#include "sphere.h"

Sphere::Sphere(const Point3D& center, double radius)
: center{center}, radius{radius} {
    if (radius < 0) {
        throw std::runtime_error("Radius cannot be less than zero!");
    }
}

Hit Sphere::construct_hit(const Ray &ray, double time) const {
    // calculate the surface normal
    Point3D point = ray.at(time);
    Vector3D normal = unit(point - center) / radius;
    return Hit{time, point, normal};
}

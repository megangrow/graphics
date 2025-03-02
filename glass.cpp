#include "glass.h"
#include "ray.h"
#include "hit.h"
#include "random.h"
#include <algorithm>

Glass::Glass(Color color, bool emitting)
        : Material{"Glass", color, emitting} {}


Ray Glass::scatter(const Ray &ray, const Hit &hit) const {
    double n1 = 1.0;
    double n2 = 1.5;
    Vector3D normal = hit.normal;
    if (dot(ray.direction, hit.normal) > 0) {
        normal *= -1;
        std::swap(n1, n2);
    }
    double cos_theta = -dot(ray.direction, normal);
    double probability = schlick(cos_theta, n1/n2); // write friday
    if (random_double() < probability) {
        Vector3D reflected = reflect(ray.direction, normal);
        return Ray{hit.position, reflected};
    }
    else {
        Vector3D refracted = refract(ray.direction, normal, n1/n2);
        return Ray{hit.position, refracted};
    }
}
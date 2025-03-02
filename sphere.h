#pragma once
#include "point3d.h"
#include "hit.h"
#include <optional>

class Ray;
class Material;

class Sphere {
public:
    Sphere(const Point3D& center, double radius, const Material* material=nullptr);

    std::optional<double> intersect(const Ray& ray) const;
    std::optional<double> intersect_geometrically(const Ray& ray) const;
    Hit construct_hit(const Ray& ray, double time) const;

    Point3D center;
    double radius;
    const Material* material;
};

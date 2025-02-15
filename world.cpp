#include "world.h"

#include "sphere.h"
#include <cmath>

void World::add(Point3D center, double radius) {
    objects.push_back(std::make_unique<Sphere>(center, radius));
}

std::optional<Hit> World::find_nearest(const Ray& ray) const {
    double time = INFINITY;
    Sphere* nearest = nullptr;
    for (const auto& object : objects) {
        std::optional<double> t = object->intersect(ray);
        if (t.value() && t.value() < time) {
            nearest = object.get();
            time = t.value();
        }
    }
    if (nearest) {
        Hit hit = nearest->construct_hit(ray, time);
        return hit;
    }
    else {
        return {};
    }
}
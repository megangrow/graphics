#include "metallic.h"
#include "ray.h"
#include "hit.h"
#include "random.h"

Metallic::Metallic(Color color, bool emitting)
        : Material{"Metallic", color, emitting} {}


Ray Metallic::scatter(const Ray &ray, const Hit &hit) const {
    Vector3D scattered = -reflect(ray.direction, hit.normal) + (fuzz * random_unit_vector());
    return Ray{hit.position, scattered};

}
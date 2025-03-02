#include "lambertian.h"
#include "ray.h"
#include "hit.h"
#include "random.h"

Lambertian::Lambertian(Color color, bool emitting)
    : Material{"Lambertian", color, emitting} {}


Ray Lambertian::scatter(const Ray &ray, const Hit &hit) const {
    Vector3D scattered = hit.normal + random_unit_vector();
    return Ray{hit.position, scattered};
}
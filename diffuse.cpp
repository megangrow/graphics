#include "diffuse.h"
#include "hit.h"
#include "random.h"
#include "ray.h"

Diffuse::Diffuse(Color color, bool emitting)
    : Material{"Diffuse", color, emitting} {}

Ray Diffuse::scatter(const Ray &ray, const Hit &hit) const {
    Vector3D scattered = random_hemisphere(hit.normal);
    return Ray{hit.position, scattered};
}
#pragma once
#include "material.h"

class Diffuse : public Material {
public:
    // hardcode name
    Ray scatter(const Ray& ray, const Hit& hit) const override;
    Diffuse(Color color, bool emitting);
};
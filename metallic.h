#pragma once
#include "material.h"

class Metallic : public Material {
public:
    Metallic(Color color, bool emitting);
    Ray scatter(const Ray& ray, const Hit& hit) const override;

private:
    double fuzz = 0.1;
};
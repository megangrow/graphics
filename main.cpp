#include "vector3d.h"
#include "ray.h"
#include <iostream>
#include <optional>
#include "sphere.h"
#include <chrono>

class A {
public:
    int data;
};

int main() {
    Sphere sphere{{0, 20, 0}, 1};
    Ray ray{{0,0,0}, {0,1,0.33}};
    std::cout << "Geometric:";
    const auto start = std::chrono::high_resolution_clock::now();
    std::optional<double> result;
    for (int i = 0; i < 1000; ++i) {
        result = sphere.intersect(ray);
    }
    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> diff = end - start;
    std::cout << diff.count() * 1e6 << "us\n";
    std::cout << "Hit? " << std::boolalpha << result.has_value() << '\n';
    if (result.has_value()) {
        double time = result.value();
        std::cout << "Distance = " << time << '\n';
        Point3D position = ray.at(time);
        std::cout << "Position = " << position << '\n';
    }

}
#include <cmath>
#include <iomanip>
#include "camera.h"
#include "sphere.h"
#include "color.h"
#include "pixels.h"
#include "ray.h"
#include "hit.h"
#include "world.h"
#include "random.h"
#include "diffuse.h"
#include "specular.h"
#include "metallic.h"
#include "lambertian.h"
#include "glass.h"

void print_progress(long long ray_num, long long total_rays);
Color trace(const World& world, const Ray& ray);
Color trace_path(const World& world, const Ray& ray, int depth);

int main() {
    // materials
    Metallic pink{{0.97, 0.61, 0.84}, false};
    Specular mirror{{0.5, 0.5, 0.5}, false};
    Diffuse lilac{{0.80, 0.42, 0.91}, false};
    Lambertian darkpurple{{0.42, 0.11, 0.38}, false};

    Diffuse gray{{0.5, 0.5, 0.5}, false};
    Diffuse light{{2,2,2}, true};
    Glass glass{{1, 1, 1}, false};
    // world
    World world;
    world.add({0, 0, -1000}, 1000, &gray);
    world.add({-1000,-1000,750}, 1000, &light);
    world.add({0, 0, 0.3}, 0.3, &mirror);
    world.add({0.75, -0.75, 0.3}, 0.3, &pink);
    world.add({0.75, 0.5, 0.3}, 0.3, &darkpurple);
    world.add({1.75, -0.35, 0.3}, 0.3, &lilac);

    // specify the number of pixels
    Pixels pixels{1280, 720};

    // create the camera
    Vector3D position{10, -2, 3}, up{0, 0, 1};
    Vector3D target{0, 0, 0};
    double fov{20};
    double aspect = static_cast<double>(pixels.columns) / pixels.rows;
    Camera camera{position, target, up, fov, aspect};

    constexpr int samples = 1000;
    constexpr int ray_depth = 10;
    const long long rays_total = pixels.rows * pixels.columns * static_cast<long long>(samples);
    long long ray_num = 0;

    for (auto row = 0; row < pixels.rows; ++row) {
        for (auto col = 0; col < pixels.columns; ++col) {
            for (int N = 0; N < samples; ++N) {
                double y = (row + random_double()) / (pixels.rows - 1);
                double x = (col + random_double()) / (pixels.columns - 1);
                // cast samples number of rays
                Ray ray = camera.compute_ray(x, y);
                pixels(row, col) += trace_path(world, ray, ray_depth);
                ++ray_num;
                if (ray_num % (rays_total/100) == 0) {
                    print_progress(ray_num, rays_total);
                }
            }
            pixels(row, col) /= samples;
        }
    }
    std::string filename{"sphere.png"};
    pixels.save_png(filename);
    std::cout << "\nWrote " << filename << '\n';
}

Color trace(const World& world, const Ray& ray) {
    std::optional<Hit> hit = world.find_nearest(ray);
    if (hit.has_value()) {
        return hit->normal;
    }
    else {
        return Black;
    }
}

Color trace_path(const World& world, const Ray& ray, int depth) {
    if (depth == 0) {
        return Black;
    }
    std::optional<Hit> hit = world.find_nearest(ray);
    if (!hit) {
        return Pink; // artifacts?
    }
    const Material * material = hit->sphere->material;
    if (material->emitting) {
        return material->color;
    }
    // more bounces!
    Ray scattered = material->scatter(ray, hit.value());
    return material->color * trace_path(world, scattered, depth-1);
}

void print_progress(long long ray_num, long long total_rays) {
    auto width = std::to_string(total_rays).length() + 4;
    int percentage = std::round(static_cast<double>(ray_num) / total_rays * 100);
    std::cout << "\rProgress: " << std::setw(3) << percentage << "% ";
    std::cout << std::setw(width) << ray_num << "/" << total_rays << " rays";
    std::cout << std::flush;
}
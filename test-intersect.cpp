#include "ray.h"
#include "pixels.h"
#include "sphere.h"
#include <iostream>
#include <chrono> // For high-resolution timing

constexpr double epsilon = 1e-5;

std::chrono::high_resolution_clock::time_point start_timer() {
    return std::chrono::high_resolution_clock::now();
}
double timer(const std::chrono::high_resolution_clock::time_point& start_time) {
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start_time;
    return duration.count(); // return time in seconds
}

int main() {
    Sphere test_sphere = {{0,10,0}, 4};
    Ray test_ray = {{0,0,0}, {0,1,0}};
    double alg_hits = 0;
    double alg_misses = 0;
    double geo_hits = 0;
    double geo_misses = 0;
    auto start_alg = std::chrono::system_clock::now();
    for (int i = 0; i < 1000; ++i) {
        auto time = test_sphere.intersect(test_ray);
        if (time) {
            ++alg_hits;
        }
        else {
            ++alg_misses;
        }
    }
    auto end_alg = std::chrono::system_clock::now();
    std::cout << "Algebraic time :" << end_alg-start_alg << ", " << alg_hits << " hits and " << alg_misses << " misses\n";
    auto start_geo = std::chrono::system_clock::now();
    for (int i = 0; i < 1000; ++i){
        auto time = test_sphere.intersect_geometrically(test_ray);
        if (time) {
            ++geo_hits;
        }
        else {
            ++geo_misses;
        }
    }
    auto end_geo = std::chrono::system_clock::now();
    std::cout << "Geometric time :" << end_geo-start_geo << ", " << geo_hits << " hits and " << geo_misses << " misses\n";

    const int rows = 720;
    const int columns = 1280;
    Sphere sphere({0, 0, -750}, 300);
    Pixels pixels{columns, rows};
    for (int row = 0; row < rows; ++row) {
        double x = row - (pixels.rows / 2.0);
        for (int col = 0; col < columns; ++col) {
            double y = col - (pixels.columns / 2.0);
            Ray test{{x, y, 0}, {0, 0, -1}};
            auto t = sphere.intersect(test);
            if (t) {
                Hit hit = sphere.construct_hit(test, t.value());
                pixels(row, col) = hit.normal;
            }
            else {
                pixels(row, col) = Black;
            }
        }
    }
    std::string filename{"ray_test.png"};
    pixels.save_png(filename);
    std::cout << "Wrote: " << filename << '\n';
}
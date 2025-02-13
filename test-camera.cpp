#include "camera.h"
#include "pixels.h"
#include "sphere.h"
#include "vector3d.h"
#include "point3d.h"
#include "hit.h"

int main() {
    Sphere ground{{0, 0, -100}, 100};
    Sphere sphere1{{1, 0.5, -90}, 0.5};
    Sphere sphere2{{0.5, 1.5, -40}, 0.5}; // creates the sphere closer to the camera
    // create camera
    Point3D position{0.5, 0.75, 100};
    Point3D target{sphere2.center};
    double fov{90};
    const int rows = 720;
    const int columns = 1280;
    Pixels pixels{columns, rows};
    double aspect = static_cast<double> (pixels.columns / pixels.rows);
    Camera camera{position, target, {0, 0, 1}, fov, aspect};

    for (int row = 0; row < pixels.rows; ++row) {
        double v = static_cast<double>(row) / (pixels.rows - 1);
        for (int col = 0; col < pixels.columns; ++col) {
            double u = static_cast<double>(col) / (pixels.columns - 1);
            Ray ray = camera.compute_ray(u, v);
            auto time = ground.intersect(ray);
            if (time.has_value()) {
                Hit hit = ground.construct_hit(ray, time.value());
                double shading = std::abs(dot(ray.direction, hit.normal));
                pixels(row, col) = White * shading;
            }
            time = sphere1.intersect(ray);
            if (time.has_value()) {
                Hit hit_2 = sphere1.construct_hit(ray, time.value());
                pixels(row, col) = hit_2.normal;
            }
            time = sphere2.intersect(ray);
            if (time.has_value()) {
                Hit hit_3 = sphere2.construct_hit(ray, time.value());
                pixels(row, col) = hit_3.normal;
            }
        }
    }
    std::string filename{"camera_move2.png"}; // This is the
    pixels.save_png(filename);
    std::cout << "Wrote: " << filename << '\n';

}
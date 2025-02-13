#define _USE_MATH_DEFINES
#include "camera.h"
#include "vector3d.h"
#include "point3d.h"
#include <cmath>
//implement
Camera::Camera(Point3D position, Point3D target, Vector3D up, double fov, double aspect)
: position{position} {
    Vector3D w = unit(target-position);
    Vector3D u = unit(cross(w,{0, 0, 1}));
    Vector3D v = cross(w, u);
    double theta = fov * (M_PI / 180);
    double width = 2 * tan(theta/2);
    double height = width/aspect;
    horizontal = width * u;
    vertical = height * v;
    Point3D upper_left_corner = position + w - 0.5*(horizontal + vertical);
}


Ray Camera::compute_ray(double s, double t) const {
    Vector3D ray_direction = unit(upper_left_corner + (horizontal * s) - (vertical * t) - position);
    return Ray{position, ray_direction};
}
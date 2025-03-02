cmake_minimum_required(VERSION 3.28)
project(raytracer)
# adjust any compiler settings
add_compile_options(-g -O2 -Wall -Wextra -pedantic -std=c++20 -march=native)
# add library for vector class and operations
add_library(vector3d vector3d.h vector3d.cpp)
# test program for vector3d
add_executable(test-vector test-vector3d.cpp)
target_link_libraries(test-vector PRIVATE vector3d)
# png support
add_library(png lodepng.h lodepng.cpp)
add_library(pixels pixels.h pixels.cpp color.h)
target_link_libraries(pixels PRIVATE png PUBLIC vector3d)
# testing pixels class
add_executable(test-pixels test-pixels.cpp)
target_link_libraries(test-pixels PRIVATE pixels)
# shapes
add_library(shapes
        sphere.h sphere.cpp
        ray.h ray.cpp
        hit.h hit.cpp
)
target_link_libraries(shapes PUBLIC vector3d)
target_link_libraries(shapes PUBLIC pixels)
add_executable(test-intersect test-intersect.cpp)
target_link_libraries(test-intersect PRIVATE shapes)

# camera
add_library(camera camera.h camera.cpp)
# test program for vector3d
add_executable(test-camera test-camera.cpp)
target_link_libraries(test-camera PRIVATE camera PUBLIC vector3d PUBLIC shapes PUBLIC pixels)

#random
add_library(random random.cpp random.h)
# test program for random
add_executable(test-random test-random.cpp)
target_link_libraries(test-random PRIVATE random PUBLIC vector3d PUBLIC shapes PUBLIC pixels)

# add library for world
add_library(world world.h world.cpp)
# test program for world
add_executable(test-world test-world.cpp)
target_link_libraries(test-world PRIVATE world PUBLIC camera PUBLIC vector3d PUBLIC shapes PUBLIC pixels PUBLIC random)

# test materials
add_executable(test-materials test-materials.cpp world.h world.cpp camera.h camera.cpp random.h random.cpp
    material.h material.cpp diffuse.h diffuse.cpp specular.h specular.cpp lambertian.cpp lambertian.h metallic.h metallic.cpp glass.h glass.cpp)
target_link_libraries(test-materials PUBLIC pixels shapes)
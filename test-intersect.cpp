#include "ray.h"
#include "pixels.h"

#include <iostream>

int main() {
    Ray ray{{0, 0, 0}, {0, 0, -1}};

    std::cout << ray << "\n";

    for (int i = 0; i < 3; ++i) {
        auto p = ray.at(i);

        std::cout << (p - ray.origin) << '\n';
    }


    // create imgae
    int rows = 720;
    int columns = 1280;
    double scale = 0.01;
    Pixels pixels{columns, rows};
    for (int row = 0; row < rows; ++row) {
        double z = scale * (row - rows/2);
        for (int col = 0; col < columns; ++col) {
            double x = scale * (col - columns/2);


        }

    }
}
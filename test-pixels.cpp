#include "pixels.h"
#include "color.h"


// write a function to set all the pixels to the same color
void set_color(Pixels& pixels, Color color) {
    for (int row = 0; row < pixels.rows; ++row) {
        for (int col = 0; col < pixels.columns; ++col) {
            // Set the color of each pixel to the given color
            pixels(row, col) = color;  // Use the non-const operator() to modify pixel color
        }
    }
}

// write a function that produces a single color gradient
void gradient(Pixels& pixels) {
    Color g = {0, 1, 0};
    for (int row = 0; row < pixels.rows; ++row) {
        g.y -= 0.0015;
        for (int col = 0; col < pixels.columns; ++col) {
            pixels(row, col) = g;
        }
    }
}

// write a function to color a pretty picture!
void pretty(Pixels& pixels) {
    for (int row = 0; row < pixels.rows; ++row) {
        for (int col = 0; col < pixels.columns; ++col) {
            if (col % 4 == 0) {
                pixels(row, col) = Pink;
            }
            else {
                pixels(row, col) = DarkGreen;
            }
        }
    }
}

int main() {
    const unsigned columns = 1280;
    const unsigned rows = 720;
    Pixels pixels{columns, rows};

    // png example:
    set_color(pixels, Lilac);
    std::string filename{"lilac.png"};
    pixels.save_png(filename);
    std::cout << "Wrote: " << filename << '\n';

    // ppm example
    set_color(pixels, DarkPurple);
    std::string filename2{"purple.ppm"};
    pixels.save_png(filename2);
    std::cout << "Wrote: " << filename2 << '\n';

    // gradient example
    gradient(pixels);
    std::string filename3{"gradient.png"};
    pixels.save_png(filename3);
    std::cout << "Wrote: " << filename3 << '\n';

    // pretty picture
    pretty(pixels);
    std::string filename4{"pretty.png"};
    pixels.save_png(filename4);
    std::cout << "Wrote: " << filename4 << '\n';
}

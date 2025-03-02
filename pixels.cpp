#include "pixels.h"
#include "lodepng.h"
#include <fstream>
#include <cmath>
#include <algorithm>

Pixels::Pixels(int columns, int rows)
  :columns{columns}, rows{rows}, values(columns*rows) {}

double gamma_correction(double value) {
    // double gamma = 2.2;
    double gamma = 1.7;
    return std::pow(value, 1/gamma);
}

template <class T>
T to_color(double value) {
// clamp value in range [0, 1)
    double clamped = std::clamp(value, 0.0, 0.999);
    clamped = gamma_correction(clamped);
// scale to 8-bit color value
    return static_cast<T>(256*clamped);
}

const Color& Pixels::operator()(int row, int col) const {
  // error handle out of range
  if (row < 0 || col < 0 || row >= rows || col >= columns) {
      throw std::overflow_error("Pixel is out of range!");
  }
  return values.at(row*columns + col);
}

Color& Pixels::operator()(int row, int col) {
    // error handle out of range
    if (row < 0 || col < 0 || row > rows || col > columns) {
        throw std::overflow_error("Pixel is out of range!");
    }
    return values.at(row*columns + col);
}

void Pixels::save_ppm(const std::string& filename) {
  // use to_color<unsigned>(color.x) for printing RGB values to file
  // write the pixel values to a file using the NetBPM ppm image format
    std::ofstream output(filename);
    if(!output) {
        throw std::runtime_error("Cannot open output file: " + filename);
    }
    output << "P3\n";
    output << columns << " " << rows << '\n';
    output << "255\n";
    for (auto c : values) {
        output << to_color<unsigned>(c.x) << " " <<
        to_color<unsigned>(c.y) << " " <<
        to_color<unsigned>(c.z) << '\n';
    }
}

void Pixels::save_png(const std::string& filename) {
  // lodepng expects pixels to be in a vector of unsigned char, where
  // the elements are R, G, B, alpha, R, G, B, alpha, etc.  Use
  // to_color<unsigned char>(color.x) for putting colors in this
  // vector, and lodepng::encode(filename, vector, width, height)
  // (make sure you check the error code returned by this function
  // using lodepng_error_text(unsigned error)).
    std::ofstream output(filename);
    if(!output) {
        throw std::runtime_error("Cannot open output file: " + filename);
    }
    std::vector<unsigned char> data;
    for (auto c : values) {
        data.push_back(to_color<unsigned char>(c.x));
        data.push_back(to_color<unsigned char>(c.y));
        data.push_back(to_color<unsigned char>(c.z));
        data.push_back(255);
    }
    unsigned error = lodepng::encode(filename, data, columns, rows);
    if (error) {
        throw std::runtime_error(lodepng_error_text(error));
    }

}

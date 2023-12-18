#pragma once

#include "vec3.h"
#include "interval.h"

#include <iostream>
#include <vector>

using namespace std;

using Color = Vec3;

void writeColor(vector<unsigned char>& image, int index, Color pixelColor, int samplesPerPixel) {
    static const Interval intensity(0, 0.999);  // Just for making sure result is withing 0-1

    auto r = pixelColor.x() / samplesPerPixel;
    auto g = pixelColor.y() / samplesPerPixel;
    auto b = pixelColor.z() / samplesPerPixel;

    image[index + 0] = static_cast<unsigned char>(256 * intensity.clamp(r));
    image[index + 1] = static_cast<unsigned char>(256 * intensity.clamp(g));
    image[index + 2] = static_cast<unsigned char>(256 * intensity.clamp(b));
}
#pragma once

#include "vec3.h"

#include <iostream>
#include <vector>

using namespace std;
using Color = Vec3;

void writeColor(vector<unsigned char>& image, int index, Color pixelColor) {
    image[index] = static_cast<unsigned char>(255.99 * pixelColor.x());
    image[index + 1] = static_cast<unsigned char>(255.99 * pixelColor.y());
    image[index + 2] = static_cast<unsigned char>(255.99 * pixelColor.z());
}
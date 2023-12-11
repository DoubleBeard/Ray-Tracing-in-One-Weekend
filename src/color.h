#pragma once

#include "vec3.h"

#include <iostream>

using namespace std;
using color = vec3;

void writeColor(ostream& out, color pixelColor) {
	out << static_cast<int>(255.999 * pixelColor.x()) << ' '
		<< static_cast<int>(255.999 * pixelColor.y()) << ' '
		<< static_cast<int>(255.999 * pixelColor.z()) << ' '
		<< endl;
}
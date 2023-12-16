// RayTracingInOneWeekend.h : Include file for standard system include files,
// or project specific include files.

#pragma once


#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "sphere.h"
#include "hittable.h"
#include "hittable_list.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "third-party/stb/stb_image_write.h"

#include <memory>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

const double DOUBLE_INFINITY = numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

inline double degToRads(double degrees) {
	return degrees * PI / 180.0;
}

﻿// RayTracingInOneWeekend.h : Include file for standard system include files,
// or project specific include files.

#pragma once


#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "sphere.h"
#include "hittable.h"
#include "hittable_list.h"
#include "interval.h"
#include "camera.h"

#include <memory>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

const double PI = 3.1415926535897932385;

inline double degToRads(double degrees) {
	return degrees * PI / 180.0;
}

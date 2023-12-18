// RayTracingInOneWeekend.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <random>

using namespace std;

const double PI = 3.1415926535897932385;

inline double degToRads(double degrees) {
	return degrees * PI / 180.0;
}

inline double randomDouble() {
	static uniform_real_distribution<double> distribution(0.0, 1.0);
	static mt19937 generator;
	return distribution(generator);
}

inline double randomDouble(double min, double max) {
	return min + (max - min) * randomDouble();
}

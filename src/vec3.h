#pragma once


#include "main.h"

#include <cmath>
#include <iostream>

using namespace std;

class Vec3 {
public:
	Vec3() : e{ 0, 0, 0 } {}
	Vec3(double x, double y, double z) : e{x, y, z} {}

	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	Vec3 operator-() const { 
		return Vec3(-e[0], -e[1], -e[2]); 
	}

	double operator[](int i) const {
		return e[i];
	}

	double& operator[](int i) {
		return e[i];
	}

	Vec3& operator+=(const Vec3& v) {
		e[0] += v.x();
		e[1] += v.y();
		e[2] += v.z();

		return *this;
	}

	Vec3& operator*=(double const t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;

		return *this;
	}

	Vec3& operator/=(double const t) {
		return *this *= 1 / t;
	}

	double length() const {
		return sqrt(lengthSquared());
	}

	double lengthSquared() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}
	
	bool isNearZero() {
		double s = 1e-8;
		return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
	}

	static Vec3 zero() {
		return Vec3();
	}

	static Vec3 one() {
		return Vec3(1, 1, 1);
	}

	static Vec3 random() {
		return Vec3(randomDouble(), randomDouble(), randomDouble());
	}

	static Vec3 random(double min, double max) {
		return Vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
	}


private:
	double e[3];

};

using Point = Vec3;

inline ostream& operator<<(ostream& out, const Vec3& v) {
	return out << '(' << v[0] << ', ' << v[1] << ', ' << v[2] << ')';
}

inline Vec3 operator+(const Vec3& u, const Vec3& v) {
	return Vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v) {
	return Vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v) {
	return Vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline Vec3 operator*(const double t, const Vec3& v) {
	return Vec3(v[0] * t, v[1] * t, v[2] * t);
}

inline Vec3 operator*(const Vec3& v, const double t) {
	return t * v;
}

inline Vec3 operator/(const Vec3& v, const double t) {
	return (1 / t) * v;
}

inline double dot(const Vec3& u, const Vec3& v) {
	return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline Vec3 cross(const Vec3& u, const Vec3& v) {
	return Vec3(
			u[1] * v[2] - u[2] * v[1],
			u[2] * v[0] - u[0] * v[2],
			u[0] * v[1] - u[1] * v[0]
		);
}

inline Vec3 unitVector(const Vec3& v) {
	return (1 / v.length()) * v;
}

inline Vec3 copyVector(const Vec3& v) {
	return Vec3(v.x(), v.y(), v.z());
}

inline Vec3 randomInUnitSphere() {
	while (true) {
		auto p = Vec3::random(-1, 1);
		if (p.lengthSquared() < 1) {
			return p;
		}
	}
}

inline Vec3 randomUnitVector() {
	return unitVector(randomInUnitSphere());
}

inline Vec3 randomOnHemisphere(const Vec3& normal) {
	Vec3 onUnitSphere = randomUnitVector();

	if (dot(onUnitSphere, normal) > 0.0) {
		return onUnitSphere;
	}
	return -onUnitSphere;
}

Vec3 reflect(const Vec3& v, const Vec3& n) {
	return v - 2 * dot(v, n) * n;
}

inline Vec3 refract(const Vec3& uv, const Vec3& n, double etaiOverEtat) {
	double cosTheta = fmin(dot(-uv, n), 1.0);
	Vec3 rOutPrep = etaiOverEtat * (uv + cosTheta * n);
	Vec3 rOutParallel = -sqrt(fabs(1.0 - rOutPrep.lengthSquared())) * n;
	return rOutPrep + rOutParallel;
}
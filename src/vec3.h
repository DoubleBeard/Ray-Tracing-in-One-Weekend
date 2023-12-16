#pragma once

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
	}

	Vec3& operator*=(double const t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
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

	static Vec3 zero() {
		return Vec3();
	}

	static Vec3 one() {
		return Vec3(1, 1, 1);
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
			u[2] * v[0] - u[0] * v[1],
			u[0] * v[1] - u[1] * v[0]
		);
}

inline Vec3 unitVector(const Vec3& v) {
	return (1 / v.length()) * v;
}

inline Vec3 copyVector(const Vec3& v) {
	return Vec3(v.x(), v.y(), v.z());
}
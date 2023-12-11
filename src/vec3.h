#pragma once

#include <cmath>
#include <iostream>

using namespace std;

class vec3 {
public:
	vec3() : e{ 0, 0, 0 } {}
	vec3(double x, double y, double z) : e{x, y, z} {}

	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	vec3 operator-() const { 
		return vec3(-e[0], -e[1], -e[2]); 
	}

	double operator[](int i) const {
		return e[i];
	}

	double& operator[](int i) {
		return e[i];
	}

	vec3& operator+=(const vec3& v) {
		e[0] += v.x();
		e[1] += v.y();
		e[2] += v.z();
	}

	vec3& operator*=(double const t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
	}

	vec3& operator/=(double const t) {
		return *this *= 1 / t;
	}

	double length() const {
		return sqrt(lengthSquared());
	}

	double lengthSquared() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}


private:
	double e[3];

};

using point3 = vec3;

inline ostream& operator<<(ostream& out, const vec3& v) {
	return out << '(' << v[0] << ', ' << v[1] << ', ' << v[2] << ')';
}

inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline vec3 operator*(const double t, const vec3& v) {
	return vec3(v[0] * t, v[1] * t, v[2] * t);
}

inline vec3 operator*(const vec3& v, const double t) {
	return t * v;
}

inline vec3 operator/(const vec3& v, const double t) {
	return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
	return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(
			u[1] * v[2] - u[2] * v[1],
			u[2] * v[0] - u[0] * v[1],
			u[0] * v[1] - u[1] * v[0]
		);
}

inline vec3 unit_vector(const vec3& v) {
	return (1 / v.length()) * v;
}
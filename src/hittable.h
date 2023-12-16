#pragma once

#include "ray.h"

class RayHit {
public:
	Point p;
	Vec3 normal;
	double t;
	bool facingFront;

	void setFaceNormal(const Ray& r, const Vec3& outwardsNormal) {
		facingFront = dot(r.direction(), outwardsNormal) < 0;
		normal = facingFront ? outwardsNormal : -outwardsNormal;
	}
};

class Hittable {
public: 
	virtual ~Hittable() = default;

	virtual bool hit(const Ray& r, double rayTMin, double rayTMax, RayHit& rec) const = 0;
};
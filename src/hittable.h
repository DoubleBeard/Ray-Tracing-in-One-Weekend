#pragma once

#include "ray.h"
#include "interval.h"

#include <memory>

class Material;

class RayHit {
public:
	Point p;
	Vec3 normal;
	shared_ptr<Material> material;
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

	virtual bool hit(const Ray& r, Interval rayT, RayHit& rec) const = 0;
};
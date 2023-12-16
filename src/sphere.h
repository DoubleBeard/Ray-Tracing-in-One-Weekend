#pragma once

#include "hittable.h"
#include "vec3.h"


class Sphere : public Hittable {
public: 
	Sphere(Point _center, double _radius) : center(_center), radius(_radius) {}

	bool hit(const Ray& r, double rayTMin, double rayTMax, RayHit& rec) const override{
		Vec3 oc = r.origin() - center;
		auto a = r.direction().lengthSquared();
		auto halfB = dot(oc, r.direction());
		auto c = oc.lengthSquared() - radius * radius;
		auto discriminant = halfB * halfB - a * c;

		if (discriminant < 0) {
			return false;
		}

		auto sqrtd = sqrt(discriminant);

		// Checking if t found is within legit t
		auto root = (-halfB - sqrtd) / a;
		if (!(rayTMin <= root && root <= rayTMax)) {
			root = (-halfB + sqrtd) / a;
			if (!(rayTMin <= root && root <= rayTMax)) {
				return false;
			}
		}

		rec.t = root;
		rec.p = r.at(root);
		Vec3 outwardsNormal = (rec.p - center) / radius;  // Vector From Center to P normalized (Same as calling unitVector, but more efficient since the length is known to be the radius)
		rec.setFaceNormal(r, outwardsNormal);
		
		return true;
	}

private:
	Point center;
	double radius;
};
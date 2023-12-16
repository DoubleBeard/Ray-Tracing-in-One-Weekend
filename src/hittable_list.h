#pragma once

#include "hittable.h"

#include <memory>
#include <vector>

using namespace std;

class HittableList : public Hittable {
public:
	vector<shared_ptr<Hittable>> objects;

	HittableList() {};
	HittableList(shared_ptr<Hittable> object) { 
		add(object);
	}

	void clear() {
		objects.clear();
	}

	void add(shared_ptr<Hittable> object) {
		objects.push_back(object);
	}

	bool hit(const Ray& r, double rayTMin, double rayTMax, RayHit& rec) const override {
		RayHit tempRec;
		bool foundHit = false;
		double closestHitDistance = rayTMax;

		for (const auto& object : objects) {
			if (object->hit(r, rayTMin, closestHitDistance, tempRec)) {
				foundHit = true;
				closestHitDistance = tempRec.t;
				rec = tempRec;
			}
		}

		return foundHit;
	}
};
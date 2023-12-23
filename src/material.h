#pragma once

#include "vec3.h"
#include "color.h"
#include "ray.h"

class RayHit;

class Material {
public:
	virtual ~Material() = default;

	virtual bool scatter(const Ray& rayIn, const RayHit& rec, Color& attenuation, Ray& scattered) const = 0;
};


class Lambertian : public Material {
public: 
	Lambertian(const Color& _albedo) : albedo(_albedo) {}

	bool scatter(const Ray& rayIn, const RayHit& rec, Color& attenuation, Ray& scattered) const override {
		Vec3 scatterDirection = rec.normal + randomUnitVector();
		
		if (scatterDirection.isNearZero()) {
			scatterDirection = rec.normal;
		}
		
		scattered = Ray(rec.p, scatterDirection);
		attenuation = albedo;

		return true;
	}

private:
	Color albedo;
};


class Metal : public Material {
public:
	Metal(const Color& _albedo) : albedo(_albedo) {}

	bool scatter(const Ray& rayIn, const RayHit& rec, Color& attenuation, Ray& scattered) const override {
		Vec3 reflected = reflect(unitVector(rayIn.direction()), rec.normal);

		scattered = Ray(rec.p, reflected);
		attenuation = albedo;

		return true;
	}

private:
	Color albedo;
};
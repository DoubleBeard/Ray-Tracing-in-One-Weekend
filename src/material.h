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
	Metal() : albedo(Color(0.5, 0.5, 0.5)), fuzziness(0) {}
	Metal(const Color& _albedo, double _fuzziness) : albedo(_albedo), fuzziness(_fuzziness) {}

	bool scatter(const Ray& rayIn, const RayHit& rec, Color& attenuation, Ray& scattered) const override {
		Vec3 reflected = reflect(unitVector(rayIn.direction()), rec.normal);

		scattered = Ray(rec.p, reflected + fuzziness * randomUnitVector());
		attenuation = albedo;

		return dot(scattered.direction(), rec.normal) > 0;
	}

private:
	Color albedo;
	double fuzziness;
};


class Dielectric : public Material {
public:
	Dielectric(double _refractionIndex, Color tint) : refractionIndex(_refractionIndex), albedo(tint) {}
	Dielectric(double _refractionIndex) : refractionIndex(_refractionIndex), albedo(Color(1.0, 1.0, 1.0)) {}

	bool scatter(const Ray& rayIn, const RayHit& rec, Color& attenuation, Ray& scattered) const override {
		attenuation = albedo;
		double refractionRatio = rec.facingFront ? (1.0 / refractionIndex) : refractionIndex;

		Vec3 unitDirection = unitVector(rayIn.direction());
		double cosTheta = fmin(dot(-unitDirection, rec.normal), 1.0);
		double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

		bool cannotRefract = refractionRatio * sinTheta > 1.0;
		Vec3 direction;

		if (cannotRefract || reflectance(cosTheta) > randomDouble()) {
			direction = reflect(unitDirection, rec.normal);
		}
		else {
			direction = refract(unitDirection, rec.normal, refractionRatio);
		}

		scattered = Ray(rec.p, direction);
		return true;
	}

private:
	Color albedo;
	double refractionIndex;

	double reflectance(double cosine) const {
		// Schlicks approximation
		auto r = pow((1 - refractionIndex) / (1 + refractionIndex), 2);
		return r + (1 - r) * pow((1 - cosine), 5);
	}
};
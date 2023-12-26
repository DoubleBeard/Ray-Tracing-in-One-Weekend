#pragma once

#include "main.h"
#include "color.h"
#include "hittable.h"
#include "material.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "third-party/stb/stb_image_write.h"

class Camera {
public:
	double aspectRatio = 1.0;
	double scale = 100;
	int samplesPerPixel = 10;
	int maxDepth = 10;

	double vFov = 90;
	Point lookFrom = Point(0, 0, -1);
	Point lookAt = Point(0, 0, 0);
	Vec3 vUp = Vec3(0, 1, 0);

	double defocusAngle = 0;
	double focusDist = 10;


	void render(const Hittable& world) {
		initialize();

		vector<unsigned char> image(imageWidth * imageHeight * channels);
		for (int j = 0; j < imageHeight; j++) {
			clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << flush;
			for (int i = 0; i < imageWidth; i++) {
				Color pixelColor{ 0, 0, 0 };

				for (int sample = 0; sample < samplesPerPixel; sample++) {
					pixelColor += rayColor(getRandomRayForPixel(i, j), maxDepth, world);
				}

				int index = (j * imageWidth + i) * channels;
				writeColor(image, index, pixelColor, samplesPerPixel);
			}
		}

		clog << "\rDone.                  " << endl;

		stbi_write_png("output.png", imageWidth, imageHeight, channels, image.data(), imageWidth * channels);
	}

private:

	int imageWidth;
	int imageHeight;
	int channels;

	Point center;
	Point startingPixel;

	Vec3 pixelDeltaU;
	Vec3 pixelDeltaV;
	Vec3 u, v, w;

	Vec3 defocusDiskU;
	Vec3 defocusDiskV;



	void initialize() {
		imageWidth = static_cast<int>(scale);
		imageHeight = static_cast<int>(scale / aspectRatio);

		imageWidth = (imageWidth > 0) ? imageWidth : 1;
		imageHeight = (imageHeight > 0) ? imageHeight : 1;

		channels = 3;

		center = lookFrom;

		double theta = degToRads(vFov);
		double h = tan(theta / 2);
		double viewportHeight = 2 * h * focusDist;
		double viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imageHeight);

		// Calculate u, v, w, unit basis vectors for the camera coordinate frame.
		w = unitVector(lookFrom - lookAt);
		u = unitVector(cross(vUp, w));
		v = cross(w, u);

		auto viewportU = viewportWidth * u;
		auto viewportV = viewportHeight * -v;

		pixelDeltaU = viewportU / imageWidth;
		pixelDeltaV = viewportV / imageHeight;

		auto viewportUpperLeft = center - (focusDist * w) - viewportU / 2 - viewportV / 2;  // Take camera position, add focal length as how deep is the viewport, then move left and up (u is towards right and v is towards down)
		startingPixel = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);  // Use upper left corner and move half U delta and half V delta

		auto defocusRadius = focusDist * tan(degToRads(defocusAngle / 2));
		defocusDiskU = u * defocusRadius;
		defocusDiskV = v * defocusRadius;
	}

	Ray getRandomRayForPixel(int i, int j) {
		auto pixelCenter = startingPixel + (i * pixelDeltaU) + (j * pixelDeltaV);
		auto samplePoint = pixelCenter + randomPixelSampleOffset();

		auto rayOrigin = (defocusAngle <= 0) ? center : defocusDiskSample();
		auto rayDirection = samplePoint - rayOrigin;

		return Ray{ rayOrigin, rayDirection };
	}

	Vec3 randomPixelSampleOffset() const {
		double px = -0.5 + randomDouble();
		double py = -0.5 + randomDouble();

		return (px * pixelDeltaU) + (py * pixelDeltaV);
	}

	Point defocusDiskSample() const {
		auto p = randomInUnitDisk();
		return center + (p[0] * defocusDiskU) + (p[1] * defocusDiskV);
	}

	Color rayColor(const Ray& r, int maxDepth, const Hittable& world) {
		RayHit rec{};

		if (maxDepth == 0) {
			return Color(0, 0, 0);
		}

		if (world.hit(r, Interval(0.001, DOUBLE_INFINITY), rec)) {
			Ray scatterRay;
			Color attenuation;

			if (rec.material->scatter(r, rec, attenuation, scatterRay)) {
				return attenuation * rayColor(scatterRay, maxDepth - 1, world);
			}

			// No need for scattering
			return Color(0, 0, 0);
		}

		auto unitDirection = unitVector(r.direction());
		auto a = 0.5 * (unitDirection.y() + 1.0);  // y is between -1 and 1 so this turns it into 0 to 1.
		return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);  // Blend values from y = 1 (blue) to y = 0 (white)
	}
};
#pragma once

#include "main.h"

#include "color.h"
#include "hittable.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "third-party/stb/stb_image_write.h"

class Camera {
public:
	double aspectRatio = 1.0;
	double scale = 100;
	int samplesPerPixel = 10;
	int maxDepth = 10;

	void render(const Hittable& world) {
		initialize();

		vector<unsigned char> image(imageWidth * imageHeight * channels);
		for (int j = 0; j < imageHeight; j++) {
			clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << flush;
			for (int i = 0; i < imageWidth; i++) {
				Color pixelColor{ 0, 0, 0 };

				for (int sample = 0; sample < samplesPerPixel; sample++) {
					pixelColor += rayColor(getRandomRayForPixel(i, j), world);
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



	void initialize() {
		imageWidth = static_cast<int>(scale);
		imageHeight = static_cast<int>(scale / aspectRatio);

		imageWidth = (imageWidth > 0) ? imageWidth : 1;
		imageHeight = (imageHeight > 0) ? imageHeight : 1;

		channels = 3;

		center = Point(0, 0, 0);

		float focalLength = 1.0;
		double viewportHeight = 2.0;
		double viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imageHeight);

		auto viewportU = Vec3(viewportWidth, 0, 0);
		auto viewportV = Vec3(0, -viewportHeight, 0);

		pixelDeltaU = viewportU / imageWidth;
		pixelDeltaV = viewportV / imageHeight;

		auto viewportUpperLeft = center - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;  // Take camera position, add focal length as how deep is the viewport, then move left and up (u is towards right and v is towards down)
		startingPixel = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);  // Use upper left corner and move half U delta and half V delta
	}

	Ray getRandomRayForPixel(int i, int j) {
		auto pixelCenter = startingPixel + (i * pixelDeltaU) + (j * pixelDeltaV);
		auto samplePoint = pixelCenter + randomPixelSampleOffset();

		return Ray{ center, samplePoint - center };
	}

	Vec3 randomPixelSampleOffset() const {
		double px = -0.5 + randomDouble();
		double py = -0.5 + randomDouble();

		return (px * pixelDeltaU) + (py * pixelDeltaV);
	}

	Color rayColor(const Ray& r, const Hittable& world) {
		RayHit rec{};

		if (world.hit(r, Interval(0, DOUBLE_INFINITY), rec)) {
			return 0.5 * (rec.normal + Vec3::one());
		}

		auto unitDirection = unitVector(r.direction());
		auto a = 0.5 * (unitDirection.y() + 1.0);  // y is between -1 and 1 so this turns it into 0 to 1.
		return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);  // Blend values from y = 1 (blue) to y = 0 (white)
	}
};
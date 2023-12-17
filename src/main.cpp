// RayTracingInOneWeekend.cpp : Defines the entry point for the application.
//

#include "main.h"

const double ASPECT_RATIO = 16.0 / 9.0;
const double SCALE = 1080;


Color rayColor(const Ray& r, const Hittable& world) {
	RayHit rec{};

	if (world.hit(r, Interval(0, DOUBLE_INFINITY), rec)) {
		return 0.5 * (rec.normal + Vec3::one());
	} 

	auto unitDirection = unitVector(r.direction());
	auto a = 0.5 * (unitDirection.y() + 1.0);  // y is between -1 and 1 so this turns it into 0 to 1.
	return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);  // Blend values from y = 1 (blue) to y = 0 (white)
}


void populateWorld(HittableList& world) {
	world.add(make_shared<Sphere>(Point(0, 0.5, -1), 0.25));
	world.add(make_shared<Sphere>(Point(0, -0.5, -1), 0.25));
	world.add(make_shared<Sphere>(Point(0.5, 0, -1), 0.25));
	world.add(make_shared<Sphere>(Point(0, 0, -5), 0.25));
	world.add(make_shared<Sphere>(Point(-0.5, 0, -1), 0.25));
	world.add(make_shared<Sphere>(Point(0, -100.5, -1), 100));
}


int main()
{
	// Using uint8_t instead of regular int (which is 4 bytes long) to avoid overflow warning when deducing from double
	int imageWidth = static_cast<int>(SCALE);
	int imageHeight = static_cast<int>(SCALE / ASPECT_RATIO);
	int channels = 3;

	imageWidth = (imageWidth > 0) ? imageWidth: 1;
	imageHeight = (imageHeight > 0) ? imageHeight : 1;


	// Camera Settings
	float focalLength = 1.0;
	double viewportHeight = 2.0;
	double viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imageHeight);
	auto cameraCenter = Point(0, 0, 0);

	// Calucalte the vectors across the horizontal and down the vertical viewport edges
	auto viewportU = Vec3(viewportWidth, 0, 0);
	auto viewportV = Vec3(0, -viewportHeight, 0);

	// Calucalte the horizontal and verical delta vectors from pixel to pixel
	auto pixelDeltaU = viewportU / imageWidth;
	auto pixelDeltaV = viewportV / imageHeight;

	// Calculate the location of the upper left pixel
	auto viewportUpperLeft = cameraCenter - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;  // Take camera position, add focal length as how deep is the viewport, then move left and up (u is towards right and v is towards down)
	auto pixel00Loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);  // Use upper left corner and move half U delta and half V delta

	// World Settings
	HittableList world;
	populateWorld(world);

	
	vector<unsigned char> image(imageWidth * imageHeight * channels);
	for (int j = 0; j < imageHeight; j++) {
		clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << flush;
		for (int i = 0; i < imageWidth; i++) {
			auto pixelCenter = pixel00Loc + (i * pixelDeltaU) + (j * pixelDeltaV);
			auto rayDirection = pixelCenter - cameraCenter;
			Ray r{ cameraCenter, rayDirection };

			int index = (j * imageWidth + i) * channels;
			writeColor(image, index, rayColor(r, world));
		}
	}

	clog << "\rDone.                  " << endl;

	stbi_write_png("output.png", imageWidth, imageHeight, channels, image.data(), imageWidth * channels);
}

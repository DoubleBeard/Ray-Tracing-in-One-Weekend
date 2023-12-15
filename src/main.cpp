// RayTracingInOneWeekend.cpp : Defines the entry point for the application.
//

#include "main.h"
#include "vec3.h"
#include "ray.h"
#include "color.h"

const double ASPECT_RATIO = 16.0 / 9.0;
const double SCALE = 400;

using namespace std;


color rayColor(const ray& r) {
	auto unitDirection = unitVector(r.direction());
	auto a = 0.5 * (unitDirection.y() + 1.0);  // y is between -1 and 1 so this turns it into 0 to 1.
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);  // Blend values from y = 1 (blue) to y = 0 (white)
}


int main()
{
	ofstream output{ "image.ppm" };

	// Using uint8_t instead of regular int (which is 4 bytes long) to avoid overflow warning when deducing from double
	int imageWidth = static_cast<int>(SCALE);
	int imageHeight = static_cast<int>(SCALE / ASPECT_RATIO);

	imageWidth = (imageWidth > 0) ? imageWidth: 1;
	imageHeight = (imageHeight > 0) ? imageHeight : 1;

	// Camera Settings

	float focalLength = 1.0;
	double viewportHeight = 2.0;
	double viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imageHeight);
	auto cameraCenter = point3(0, 0, 0);

	// Calucalte the vectors across the horizontal and down the vertical viewport edges
	auto viewportU = vec3(viewportWidth, 0, 0);
	auto viewportV = vec3(0, -viewportHeight, 0);

	// Calucalte the horizontal and verical delta vectors from pixel to pixel
	auto pixelDeltaU = viewportU / imageWidth;
	auto pixelDeltaV = viewportV / imageHeight;

	// Calculate the location of the upper left pixel
	auto viewportUpperLeft = cameraCenter - vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;  // Take camera position, add focal length as how deep is the viewport, then move left and up (u is towards right and v is towards down)
	auto pixel00Loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);  // Use upper left corner and move half U delta and half V delta

	output << "P3" << endl << imageWidth << ' ' << imageHeight << endl << 255 << endl;

	for (int j = 0; j < imageHeight; j++) {
		clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << flush;
		for (int i = 0; i < imageWidth; i++) {
			auto pixelCenter = pixel00Loc + (i * pixelDeltaU) + (j * pixelDeltaV);
			auto rayDirection = pixelCenter - cameraCenter;
			ray r{ cameraCenter, rayDirection };

			writeColor(output, rayColor(r));
		}
	}

	clog << "\rDone.                  " << endl;
	output.close();
}

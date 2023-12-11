// RayTracingInOneWeekend.cpp : Defines the entry point for the application.
//

#include "main.h"
#include "vec3.h"
#include "color.h"

using namespace std;

int main()
{

	ofstream output("image.ppm");

	int imageWidth = 256;
	int imageHeight = 256;

	output << "P3" << endl << imageWidth << ' ' << imageHeight << endl << 255 << endl;

	for (double j = 0; j < imageHeight; j++) {
		clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << flush;
		for (double i = 0; i < imageWidth; i++) {
			color pixelColor = color(i / (imageWidth - 1), j / (imageHeight - 1), 0);
			writeColor(output, pixelColor);
		}
	}

	clog << "\rDone.                  " << endl;
	output.close();
}

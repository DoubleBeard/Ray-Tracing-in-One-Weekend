// RayTracingInOneWeekend.cpp : Defines the entry point for the application.
//

#include "RayTracingInOneWeekend.h"

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
			int r = static_cast<int>((double)(i / (imageWidth - 1)) * 255.999);
			int g = static_cast<int>((double)(j / (imageHeight - 1)) * 255.999);

			output << r << ' ' << g << ' ' << 0 << endl;
		}
	}

	clog << "\rDone.                  " << endl;
	output.close();
}

// RayTracingInOneWeekend.cpp : Defines the entry point for the application.
//

#include "main.h"

const double ASPECT_RATIO = 16.0 / 9.0;
const double SCALE = 1080;


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
	HittableList world;
	populateWorld(world);

	Camera mainCamera;

	mainCamera.aspectRatio = ASPECT_RATIO;
	mainCamera.scale = SCALE;
	
	mainCamera.render(world);
}

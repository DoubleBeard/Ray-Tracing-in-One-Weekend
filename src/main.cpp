// RayTracingInOneWeekend.cpp : Defines the entry point for the application.
//

#include "main.h"
#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "sphere.h"
#include "hittable.h"
#include "hittable_list.h"
#include "interval.h"
#include "camera.h"

#include <memory>
#include <iostream>
#include <fstream>
#include <filesystem>

const double ASPECT_RATIO = 16.0 / 9.0;
const double SCALE = 1080;


void populateWorld(HittableList& world) {
	world.add(make_shared<Sphere>(Point(0, 0, -1), 0.5));
	world.add(make_shared<Sphere>(Point(0, -100.5, -1), 100));
}


int main()
{
	HittableList world;
	populateWorld(world);

	Camera mainCamera;

	mainCamera.aspectRatio = ASPECT_RATIO;
	mainCamera.scale = SCALE;
	mainCamera.samplesPerPixel = 100;
	mainCamera.maxDepth = 50;
	
	mainCamera.render(world);
}

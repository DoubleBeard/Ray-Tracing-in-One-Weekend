// RayTracingInOneWeekend.cpp : Defines the entry point for the application.
//

#pragma once

#include "main.h"
#include "vec3.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"
#include "material.h"

#include <memory>
#include <iostream>
#include <fstream>
#include <filesystem>	

const double ASPECT_RATIO = 16.0 / 9.0;
const double SCALE = 1080;


void populateWorld(HittableList& world) {
	shared_ptr<Material> redLambertian = make_shared<Lambertian>(Color(0.8, 0, 0));
	shared_ptr<Material> greenLambertian = make_shared<Lambertian>(Color(0, 0.8, 0));
	world.add(make_shared<Sphere>(Point(0, 0, -1), 0.5, redLambertian));
	world.add(make_shared<Sphere>(Point(0, -100.5, -1), 100, greenLambertian));
}


int main()
{
	HittableList world;
	populateWorld(world);

	Camera mainCamera;

	mainCamera.aspectRatio = ASPECT_RATIO;
	mainCamera.scale = SCALE;
	mainCamera.samplesPerPixel = 30;
	mainCamera.maxDepth = 50;
	
	mainCamera.render(world);
}

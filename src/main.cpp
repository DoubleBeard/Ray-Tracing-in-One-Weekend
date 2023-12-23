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
const double SCALE = 400;


void populateWorld(HittableList& world) {
	auto redLambertian = make_shared<Lambertian>(Color(0.8, 0, 0));
	auto greenLambertian = make_shared<Lambertian>(Color(0, 0.8, 0));
	auto silverMetal = make_shared<Metal>(Color(0.5, 0.5, 0.5), 0.2);
	auto yellowTintMetal = make_shared<Metal>(Color(0.8, 0.8, 0), 0.8);
	auto glass = make_shared<Dielectric>(1.5);

	// Base Lambertian Speheres
	world.add(make_shared<Sphere>(Point(0, 0, -1), 0.5, redLambertian));
	world.add(make_shared<Sphere>(Point(0, -100.5, -1), 100, greenLambertian));
	
	// Metal Spheres
	world.add(make_shared<Sphere>(Point(-1.2, 0, -1), 0.5, silverMetal));

	// Glass Speheres
	world.add(make_shared<Sphere>(Point(1.2, 0, -1), 0.5, glass));
	world.add(make_shared<Sphere>(Point(1.2, 0, -1), -0.4, glass));				// Makes the glass sphere hollow
}


int main()
{
	HittableList world;
	populateWorld(world);

	Camera mainCamera;

	mainCamera.aspectRatio = ASPECT_RATIO;
	mainCamera.scale = SCALE;
	mainCamera.samplesPerPixel = 100;
	mainCamera.maxDepth = 10;
	
	mainCamera.render(world);
}

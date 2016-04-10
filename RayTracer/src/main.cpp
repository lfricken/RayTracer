#include "stdafx.hpp"
#include "World.hpp"
#include "Ray.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"
#include "Light.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "Rectangle.hpp"
#include "SquareLight.hpp"

using namespace leon;
using namespace std;

/// <summary>
/// Main function/program entry point.
/// </summary>
/// <returns>0 if everything went well</returns>
int main()
{
	int floorSize = 1000;
	int floorHeight = 0;
	int lightHeight = 90;
	int lightSize = 5;
	int lightDist = 45;

	sptr<World> spWorld(new World());
	World& world = *spWorld;


	Geometry* s = NULL;
	Light* l = NULL;


	s = new Rectangle(Vector(lightDist - (lightSize / 2), 20 - (lightSize / 2), lightHeight), Vector(lightSize, 0, 0), Vector(0, lightSize, 0));
	s->material.color = sf::Color::Red;
	s->material.diffuse = 1;
	s->material.specular = 1;
	world.add(s);
	l = new SquareLight(sf::Color::White, (Rectangle*)s, 1);

	//l = new PointLight(sf::Color(255, 255, 255), Vector(lightDist, 0, lightHeight));

	world.lights.push_back(sptr<Light>(l));

	world.camera.eyedist = 60;


	s = new Sphere(Vector(45, -40, 35), 35);
	s->material.color = sf::Color::Cyan;
	s->material.specular = 1;
	s->material.diffuse = 1;
	s->material.reflection = 0.5;
	world.add(s);

	s = new Sphere(Vector(30, 100, 25), 25);
	s->material.color = sf::Color::Green;
	s->material.specular = 1;
	s->material.diffuse = 1;
	s->material.reflection = 0.9;
	world.add(s);

	s = new Sphere(Vector(-40, 40, 20), 20);
	s->material.color = sf::Color(128, 128, 255);
	s->material.specular = 0.2;
	s->material.diffuse = 1;
	s->material.reflection = 0.1;
	world.add(s);

	s = new Sphere(Vector(-50, -50, 20), 20);
	s->material.color = sf::Color(0, 0, 255);
	s->material.specular = 0.1;
	s->material.diffuse = 1;
	s->material.reflection = 0.3;
	world.add(s);

	s = new Plane(Vector(0, 0, floorHeight), Vector(0, 0, 1));
	s->material.color = sf::Color::Red;
	s->material.diffuse = 1;
	s->material.specular = 1;
	s->material.reflection = 0.2;
	world.add(s);



	//world.loadModel(100, "cow.obj", Vector(100, 20, -30));

	world.camera.move(Vector(-60, -60, 90), world);
	//world.camera.roll(45 * 3.14 / 180, world);
	world.camera.yaw(35 * 3.14 / 180, world);
	world.camera.pitch(45 * 3.14 / 180, world);

	//world.redoOctree();

	int resX = 1920;
	int resY = 1080;
	int frameX = 100;
	int frameY = (float)resY / (float)((float)resX / (float)frameX);
	int samples = 1;

	world.render(resX, resY, frameX, frameY, RenderMode::PerspectivePlane, SampleMode::PerPixel, samples);//img5
	world.save(content + "frame_perspective3_Jitter.png");

	cout << "\n\nUsed " << resX * resY * samples << " rays.";

	cout << "\nPress Enter to continue...";
	cin.get();
	
	return 0;
}
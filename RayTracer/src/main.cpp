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
	int floorHeight = -100;
	int lightHeight = 90;
	int lightSize = 20;
	int lightDist = 100;

	sptr<World> spWorld(new World());
	World& world = *spWorld;


	Geometry* s = NULL;
	Light* l = NULL;


	//s = new Rectangle(Vector(lightDist - (lightSize / 2), -(lightSize / 2), lightHeight), Vector(lightSize, 0, 0), Vector(0, lightSize, 0));
	//s->material.color = sf::Color::Red;
	//s->material.diffuse = 1;
	//s->material.specular = 1;
	//world.add(s);
	//l = new SquareLight(sf::Color::White, (Rectangle*)s);

	l = new PointLight(sf::Color(255, 255, 255), Vector(lightDist, 0, lightHeight));

	world.lights.push_back(sptr<Light>(l));

	world.camera.eyedist = 35;


	s = new Sphere(Vector(100, 100, 0), 25);
	s->material.color = sf::Color::Green;
	s->material.specular = 1;
	s->material.diffuse = 1;
	world.add(s);

	s = new Sphere(Vector(70, -40, 0), 35);
	s->material.color = sf::Color::Cyan;
	s->material.specular = 1;
	s->material.diffuse = 1;
	world.add(s);


	s = new Rectangle(Vector(0, -floorSize / 2, floorHeight), Vector(floorSize, 0, 0), Vector(0, floorSize, 0));
	s->material.color = sf::Color::Red;
	s->material.diffuse = 1;
	s->material.specular = 1;
	world.add(s);

	//Geometry* at = new Triangle(Vector(512, 512, 300), Vector(512, 512, -600), Vector(512, -512, 0));
	//at->color = sf::Color::Cyan;
	//world.add(at);

	//world.loadModel(100, "cow.obj", Vector(100, 20, -30));

	//world.camera.move(Vector(100, 10, 0), world);
	//world.camera.yaw(70 * 3.14 / 180, world);
	//world.camera.pitch(60 * 3.14 / 180, world);

	world.redoOctree();

	world.render(512, 512, 100, 100, RenderMode::PerspectivePlane, SampleMode::PerPixel, 1);//img5
	world.save(content + "frame_perspective3_Jitter.png");
	return 0;
}
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
	sptr<World> spWorld(new World());
	World& world = *spWorld;

	Geometry* s = NULL;

	//Light* l = new PointLight(sf::Color(255, 255, 255), Vector(50, -10, 0));
	s = new Rectangle(Vector(0, -300, 0), Vector(0, 0, -50), Vector(0, -50, 0));
	s->material.color = sf::Color::Red;
	s->material.diffuse = 1;
	s->material.specular = 1;

	Light* l = new SquareLight(sf::Color::White, (Rectangle*)s);
	world.lights.push_back(sptr<Light>(l));

	world.camera.eyedist = 35;


	//int num = 20;//squared
	//int startY = 500;
	//int startZ = 500;
	//int increment = 20;
	//int radius = 10;
	//for(int y = 0; y < num; ++y)
	//	for(int z = 0; z < num; ++z)
	//	{
	//		s = new Sphere(Vector(600, startY - y * increment, startZ - z * increment), radius);
	//		s->material.color = sf::Color(y*40, 255, z*10);
	//		s->material.specular = 0;
	//		world.add(s);
	//	}



	s = new Sphere(Vector(300, 100, 100), 35);
	s->material.color = sf::Color::Green;
	s->material.specular = 0;
	s->material.diffuse = 1;
	world.add(s);

	s = new Sphere(Vector(300, 0, 0), 25);
	s->material.color = sf::Color::Cyan;
	s->material.specular = 0;
	s->material.diffuse = 1;
	world.add(s);

	s = new Rectangle(Vector(400, 400, 400), Vector(0, 0, -400), Vector(0, -400, 0));
	s->material.color = sf::Color::Red;
	s->material.diffuse = 1;
	s->material.specular = 1;
	world.add(s);

	//s = new Triangle(Vector(400, 400, 400), Vector(400, 0, 0), Vector(400, 0, 400));
	//s->material.color = sf::Color::Red;
	//s->material.diffuse = 1;
	//s->material.specular = 1;
	//world.add(s);

	//s = new Triangle(Vector(400, 400, 400), Vector(400, 400, 0), Vector(400, 0, 0));
	//s->material.color = sf::Color::Red;
	//s->material.diffuse = 1;
	//s->material.specular = 1;
	//world.add(s);

	//Geometry* at = new Triangle(Vector(512, 512, 300), Vector(512, 512, -600), Vector(512, -512, 0));
	//at->color = sf::Color::Cyan;
	//world.add(at);

	//world.loadModel(100, "cow.obj", Vector(100, 20, -30));

	//world.camera.move(Vector(100, 10, 0), world);
	//world.camera.yaw(70 * 3.14 / 180, world);
	//world.camera.pitch(60 * 3.14 / 180, world);

	world.redoOctree();

	world.render(512, 512, 100, 100, RenderMode::PerspectivePlane, SampleMode::MultiJitter, 8);//img5
	world.save(content + "frame_perspective3_Jitter.png");
	return 0;
}
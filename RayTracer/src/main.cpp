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
	Light* l = NULL;

	int areaLightDim = 10;
	s = new Rectangle(Vector(400 - areaLightDim, -areaLightDim, 100), Vector(areaLightDim * 2, 0, 0), Vector(0, areaLightDim * 2, 0));
	s->material.color = sf::Color::Red;
	s->material.diffuse = 1;
	s->material.specular = 1;


	//l = new PointLight(sf::Color(255, 255, 255), Vector(0, 0, 50));
	l = new SquareLight(sf::Color::White, (Rectangle*)s);
	world.lights.push_back(sptr<Light>(l));

	world.camera.eyedist = 35;


	//s = new Sphere(Vector(300, 100, 100), 35);
	//s->material.color = sf::Color::Green;
	//s->material.specular = 0;
	//s->material.diffuse = 1;
	//world.add(s);

	//s = new Sphere(Vector(300, 0, 0), 25);
	//s->material.color = sf::Color::Cyan;
	//s->material.specular = 0;
	//s->material.diffuse = 1;
	//world.add(s);

	s = new Rectangle(Vector(0, -400, -100), Vector(800, 0, 0), Vector(0, 800, 0));
	s->material.color = sf::Color::Red;
	s->material.diffuse = 1;
	s->material.specular = 0;
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
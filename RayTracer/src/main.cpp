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
#include "Instance.hpp"

using namespace leon;
using namespace std;

/// <summary>
/// Main function/program entry point.
/// </summary>
/// <returns>0 if everything went well</returns>
int main()
{
	sf::Clock clock;

	sf::Time time = clock.getElapsedTime();

	float t = time.asSeconds();

	int floorSize = 1000;
	int floorHeight = -50;
	int lightHeight = 90;
	int lightSize = 8;
	int lightDist = 0;

	sptr<World> spWorld(new World());
	World& world = *spWorld;

	Instance* i = NULL;
	Geometry* s = NULL;
	Light* l = NULL;


	//s = new Rectangle(Vector(lightDist - (lightSize / 2), 20 - (lightSize / 2), lightHeight), Vector(lightSize, 0, 0), Vector(0, lightSize, 0));
	//s->material.color = sf::Color::Red;
	//s->material.diffuse = 1;
	//s->material.specular = 1;
	//world.add(s);
	//l = new SquareLight(sf::Color::White, (Rectangle*)s, 3);

	l = new PointLight(sf::Color(255, 255, 255), Vector(lightDist, 0, lightHeight));

	world.lights.push_back(sptr<Light>(l));

	world.camera.eyedist = 60;


	s = new Sphere(Vector(45, -20, 0), 15);
	s->material.color = sf::Color::Cyan;
	s->material.specular = 1;
	s->material.diffuse = 1;
	s->material.reflection = 0;
	s->m_spTexture.reset(new sf::Image());
	s->m_spTexture->loadFromFile(content + "textures/bad.png");
	world.add(s);

	s = new Sphere(Vector(40, 25, 0), 25);
	s->material.color = sf::Color::Green;
	s->material.specular = 1;
	s->material.diffuse = 1;
	s->material.reflection = 0.5;
	world.add(s);

	s = new Plane(Vector(0, 0, floorHeight), Vector(0, 0, 1));
	s->material.color = sf::Color::Red;
	s->material.diffuse = 1;
	s->material.specular = 1;
	s->material.reflection = 0.3;
	world.add(s);



	//world.loadModel(100, "cow.obj", Vector(100, 20, -30));

	//world.camera.move(Vector(-60, -60, 90), world);
	////world.camera.roll(45 * 3.14 / 180, world);
	//world.camera.yaw(35 * 3.14 / 180, world);
	//world.camera.pitch(45 * 3.14 / 180, world);

	//world.redoOctree();

	int resX = 800;
	int resY = 800;
	int frameX = 100;
	int frameY = (float)resY / (float)((float)resX / (float)frameX);
	int samples = 1;

	world.render(resX, resY, frameX, frameY, RenderMode::PerspectivePlane, SampleMode::PerPixel, samples);//img5
	world.save(content + "frame_perspective3_Jitter.png");

	time = clock.getElapsedTime();
	float t2 = time.asSeconds();

	cout << "\n\nUsed " << world.numRays << " rays in " << t2-t << " seconds.";

	cout << "\nPress Enter to continue...";
	cin.get();
	
	return 0;
}
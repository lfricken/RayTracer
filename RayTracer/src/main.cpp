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
	int floorHeight = -40;
	int lightHeight = 0;
	int lightSize = 8;
	int lightDist = -70;

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

	l = new PointLight(sf::Color(255, 255, 255), Vector(lightDist, 30, lightHeight));

	world.lights.push_back(sptr<Light>(l));

	world.camera.eyedist = 80;


	s = new Sphere(Vector(20, -20, 0), 15);
	s->material.color = sf::Color::Cyan;
	s->material.specular = 0.0;
	s->material.diffuse = 0.5;
	s->material.reflection = 0;
	s->material.gloss = 1;
	s->material.glossRootSamples = 4;
	s->material.glossRootDimensions = 0.2;
	world.add(s);

	s = new Sphere(Vector(15, -20, 30), 10);
	s->material.color = sf::Color::Yellow;
	s->material.specular = 1;
	s->material.diffuse = 1;
	s->material.reflection = 0;
	world.add(s);


	s = new Sphere(Vector(12, 1, -5), 5);
	s->material.color = sf::Color::White;
	s->material.specular = 0.f;
	s->material.diffuse = 0.f;
	s->material.reflection = 0.f;
	s->material.transparency = 0.9f;
	s->material.indexRefraction = 1.5f;
	world.add(s);


	s = new Sphere(Vector(40, 25, 0), 25);
	s->material.color = sf::Color::Green;
	s->material.specular = 1;
	s->material.diffuse = 1;
	s->material.reflection = 0.5f;

	s->m_spTexture.reset(new sf::Image());
	s->m_spTexture->loadFromFile(content + "textures/bad.png");
	world.add(s);

	s = new Plane(Vector(0, 0, floorHeight), Vector(0, 0, 1));
	s->material.color = sf::Color::Red;
	s->material.diffuse = 1;
	s->material.specular = 1;
	s->material.reflection = 1;
	world.add(s);

	//s = new Triangle(Vector(30, 0, 0), Vector(30, -15, 0), Vector(30, 0, 15));
	//s->material.color = sf::Color::Cyan;
	//s->material.diffuse = 1;
	//s->material.specular = 1;
	//s->material.reflection = 0;
	//world.add(s);

	//s = new Rectangle(Vector(30, 0, 0), Vector(0, -5, 0), Vector(0, 0, -5));
	//s->material.color = sf::Color::Cyan;
	//s->material.diffuse = 1;
	//s->material.specular = 1;
	//s->material.reflection = 0;
	//world.add(s);

	//world.loadModel(100, "cow.obj", Vector(100, 20, -30));

	//world.camera.move(Vector(-10, 0, 40), world);
	//////world.camera.roll(45 * 3.14 / 180, world);
	////world.camera.yaw(35 * 3.14 / 180, world);
	//world.camera.pitch(25 * 3.14 / 180, world);

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

	cout << "\n\nUsed " << world.numRays << " rays in " << t2 - t << " seconds.";

	cout << "\nPress Enter to continue...";
	cin.get();

	return 0;
}
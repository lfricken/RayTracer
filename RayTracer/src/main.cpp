#include "stdafx.hpp"
#include "World.hpp"
#include "Ray.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"
#include "Light.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"

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

	Light* l = new PointLight(sf::Color(255, 255, 255), Vector(200, 0, 0));
	world.lights.push_back(sptr<Light>(l));

	world.camera.eyedist = 35;


	int num = 40;//squared
	int startY = 800;
	int startZ = 800;
	int increment = 35;
	int radius = 15;
	for(int y = 0; y < num; ++y)
		for(int z = 0; z < num; ++z)
		{
			s = new Sphere(Vector(600, startY - y * increment, startZ - z * increment), radius);
			s->color = sf::Color(y*40, 255, z*10);
			world.add(s);
		}


	s = new Sphere(Vector(300, 100, 100), 35);
	s->color = sf::Color::Green;
	world.add(s);



	//Geometry* at = new Triangle(Vector(512, 512, 300), Vector(512, 512, -600), Vector(512, -512, 0));
	//at->color = sf::Color::Cyan;
	//world.add(at);

	//world.loadModel(100, "cow.obj", Vector(100, 20, -30));

	//world.camera.move(Vector(100, 10, 0), world);
	//world.camera.yaw(70 * 3.14 / 180, world);
	//world.camera.pitch(60 * 3.14 / 180, world);

	world.redoOctree();

	world.render(512, 512, 100, 100, RenderMode::PerspectivePlane, SampleMode::MultiJitter, 2);//img5
	world.save(content + "frame_perspective3_Jitter.png");
	return 0;
}
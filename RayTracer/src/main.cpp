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
		


	Geometry* at = new Triangle(Vector(512, 512, 300), Vector(512, 512, -600), Vector(512, -512, 0));
	at->color = sf::Color::Cyan;
	world.add(at);

	world.loadModel(100, "cow.obj", Vector(100, 20, -30));

	Light* l = new PointLight(sf::Color(255, 255, 255), Vector(0, 0, 40));
	world.lights.push_back(sptr<Light>(l));



	world.camera.eyedist = 40;
	world.camera.move(Vector(100, 10, 0), world);
	world.camera.yaw(70 * 3.14 / 180, world);
	world.camera.pitch(60 * 3.14 / 180, world);

	world.redoOctree();

	world.render(512, 512, 100, 100, RenderMode::PerspectivePlane, SampleMode::PerPixel, 1);//img5
	world.save(content + "frame_perspective3_Jitter.png");
	return 0;
}
#include "stdafx.hpp"
#include "World.hpp"
#include "Ray.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"
#include "Light.hpp"
#include "DirectionalLight.hpp"

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
		
	s = new Sphere(Vector(512, 512, 512), 50);
	s->color = sf::Color::Green;
	world.add(s);

	s = new Sphere(Vector(512, 512, -512), 50);
	s->color = sf::Color::Yellow;
	world.add(s);

	s = new Sphere(Vector(512, -512, 512), 50);
	s->color = sf::Color::Cyan;
	world.add(s);


	//s = new Triangle(Vector(200, 0, -40), Vector(200, 0, -60), Vector(200, -50, -40));
	//world.add(s);

	//Geometry* at = new Triangle(Vector(140, 0, 90), Vector(140, 0, -110), Vector(140, -200, 90));
	//at->color = sf::Color::Cyan;
	//world.geometry.push_back(sptr<Geometry>(at));


	Light* l = new DirectionalLight(sf::Color(255, 255, 255), Vector(1, 1, -1));
	world.lights.push_back(sptr<Light>(l));

	world.camera.eyedist = 40;

	//world.render(400, 400, 100, 100, RenderMode::Orthographic);//img1
	//world.save(content + "frame1_orthographic1.png");

	//world.render(400, 400, 100, 100, RenderMode::PerspectivePlane);//img2
	//world.save(content + "frame1_perspective1.png");

	//world.camera.yaw(-0.3, world);
	//world.render(400, 400, 100, 100, RenderMode::PerspectivePlane);//img3
	//world.save(content + "frame1_perspective2.png");


	//world.camera.yaw(0.3, world);
	//world.render(400, 400, 100, 100, RenderMode::PerspectivePlane);//img4
	//world.save(content + "frame_perspective3_noJitter.png");

	world.render(400, 400, 100, 100, RenderMode::PerspectivePlane, SampleMode::PerPixel, 1);//img5
	world.save(content + "frame_perspective3_Jitter.png");
	return 0;
}
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
		
	s = new Sphere(Vector(200, 0, 0), 50);
	s->color = sf::Color(255, 255, 255);
	world.geometry.push_back(sptr<Geometry>(s));

	s = new Sphere(Vector(200, 30, 0), 50);
	s->color = sf::Color(200, 255, 255);
	world.geometry.push_back(sptr<Geometry>(s));

	s = new Sphere(Vector(100, -120, 20), 50);
	s->color = sf::Color(200, 69, 40);
	world.geometry.push_back(sptr<Geometry>(s));


	Geometry* t = new Triangle(Vector(200, 0, 0), Vector(200, 0, -200), Vector(200, -200, 0));
	world.geometry.push_back(sptr<Geometry>(t));

	//Geometry* at = new Triangle(Vector(140, 0, 90), Vector(140, 0, -110), Vector(140, -200, 90));
	//at->color = sf::Color::Cyan;
	//world.geometry.push_back(sptr<Geometry>(at));


	Light* l = new DirectionalLight(sf::Color(255, 255, 255), Vector(1, 1, -1));
	world.lights.push_back(sptr<Light>(l));

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
#include "stdafx.hpp"
#include "World.hpp"
#include "Ray.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"
#include "Light.hpp"
#include "DirectionalLight.hpp"

using namespace leon;
using namespace std;

int main()
{
	sptr<World> spWorld(new World());
	World& world = *spWorld;

	Geometry* s = NULL;
		
	s = new Sphere(Vector(200, 0, 0), 50);
	s->color = sf::Color(255, 255, 255);
	world.geometry.push_back(sptr<Geometry>(s));

	s = new Sphere(Vector(200, 100, 0), 50);
	s->color = sf::Color(200, 255, 255);
	world.geometry.push_back(sptr<Geometry>(s));

	s = new Sphere(Vector(100, -100, 20), 50);
	s->color = sf::Color(200, 69, 40);
	world.geometry.push_back(sptr<Geometry>(s));


	Geometry* t = new Triangle(Vector(50, 0, 0), Vector(50, 0, -20), Vector(50, -20, 0));
	world.geometry.push_back(sptr<Geometry>(t));


	Light* l = new DirectionalLight(sf::Color(255, 255, 255), Vector(1, 1, -1));
	world.lights.push_back(sptr<Light>(l));

	world.render(400, 400, 100, 100, RenderMode::Orthographic);//img1
	world.save(content + "frame_Ortho.png");
	world.render(400, 400, 100, 100, RenderMode::PerspectivePlane);//img2
	world.save(content + "frame_PerspPlane.png");


	world.camera.yaw(-0.3, world);
	world.render(400, 400, 100, 100, RenderMode::PerspectivePlane);
	world.save(content + "frame_PerspPlane3.png");
	world.camera.yaw(-0.6, world);
	world.render(400, 400, 100, 100, RenderMode::PerspectivePlane);
	world.save(content + "frame_PerspPlane6.png");
	return 0;
}
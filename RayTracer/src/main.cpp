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

	//Geometry* t = new Triangle(Vector(10, 10, 0), Vector(10, -10, 0), Vector(20, 0, 0));
	//Geometry* t2 = new Triangle(Vector(10, -10, 0), Vector(15, -20, -10), Vector(20, 0, 0));
	Geometry* s = NULL;
		
	s = new Sphere(Vector(200, 0, 0), 50);
	s->color = sf::Color(255, 255, 255);
	world.geometry.push_back(sptr<Geometry>(s));

	s = new Sphere(Vector(200, 100, 0), 50);
	s->color = sf::Color(200, 255, 255);
	world.geometry.push_back(sptr<Geometry>(s));

	s = new Sphere(Vector(100, -100, 0), 50);
	s->color = sf::Color(200, 69, 40);
	world.geometry.push_back(sptr<Geometry>(s));

	Light* l = new DirectionalLight(sf::Color(255, 255, 255), Vector(1, 1, -1));



	//world.geometry.push_back(sptr<Geometry>(t));
	//world.geometry.push_back(sptr<Geometry>(t2));

	world.lights.push_back(sptr<Light>(l));

	world.render(400, 400, 100, 100, RenderMode::Orthographic);
	world.save(content + "frame_Ortho.png");
	world.render(400, 400, 100, 100, RenderMode::PerspectivePlane);
	world.save(content + "frame_PerspPlane.png");
	return 0;
}
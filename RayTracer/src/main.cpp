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

	Geometry* t = new Triangle(Vector(10, 10, 0), Vector(10, -10, 0), Vector(20, 0, 0));
	Geometry* s = new Sphere(Vector(0, 20, 0), 10);
	Light* l = new DirectionalLight(sf::Color(255, 255, 255), Vector(1, 1, -1));

	s->color = sf::Color(30, 180, 30);
	t->color = sf::Color(50, 50, 50);

	world.geometry.push_back(sptr<Geometry>(t));
	world.geometry.push_back(sptr<Geometry>(s));
	world.lights.push_back(sptr<Light>(l));

	world.camera.position = Vector(0, 0, 1024);
	world.camera.direction = Vector(0, 0, -1);
	world.render(400, 400, 0.2, 0.2, RenderMode::Orthographic);
	world.save(content + "frame.png");
	return 0;
}
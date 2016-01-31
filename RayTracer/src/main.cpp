#include "stdafx.hpp"
#include "World.hpp"
#include "Ray.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"

using namespace leon;
using namespace std;

int main()
{
	sptr<World> spWorld(new World());
	World& world = *spWorld;

	Geometry* t = new Triangle(Vector(10, 10, 0), Vector(10, -10, 0), Vector(20, 0, 0));
	Geometry* s = new Sphere(Vector(0, 0, 0), 10);

	world.addGeometry(sptr<Geometry>(t));
	world.addGeometry(sptr<Geometry>(s));

	world.camera.position = Vector(0, 0, 1024);
	world.camera.direction = Vector(0, 0, -1);
	world.render(100, 100, RenderMode::Orthographic);
	world.save(content + "frame.png");
	return 0;
}
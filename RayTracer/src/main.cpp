#include "stdafx.hpp"
#include "World.hpp"
#include "Ray.hpp"
#include "Triangle.hpp"

using namespace leon;
using namespace std;

int main()
{

	Ray r(Vector(0,0,0), Vector(1, 0, 0));

	Triangle t(Vector(4, -1, 1), Vector(4, -1, -1), Vector(4, -2, 0));

	Vector right(1, 0, 0);
	Vector up(0, 1, 0);
	Vector o(0, 0, 0);

	double dot = o.area((o.to(up)), o.to(right));

	Vector b = t.intersects(r);
	bool FALSE = b.init;
	sptr<World> spWorld(new World());
	spWorld->render();
	spWorld->setPixel(1);
	spWorld->save(content + "frame.png");
	return 0;
}
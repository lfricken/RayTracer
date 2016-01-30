#include "stdafx.hpp"
#include "World.hpp"
#include "Ray.hpp"

using namespace leon;

int main()
{
	Ray r;
	sptr<World> spWorld(new World());
	spWorld->render();
	spWorld->setPixel(1);
	spWorld->save(content + "frame.png");
	return 0;
}
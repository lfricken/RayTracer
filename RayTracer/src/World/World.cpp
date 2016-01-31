#include "World.hpp"
#include "Ray.hpp"

using namespace std;
using namespace leon;

World::World()
{
	spWindow = sptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(512, 512), "Leon's Ray Tracer: 2016 Edition"));
	image.create(512, 512, sf::Color(128, 128, 128, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}
World::~World()
{

}
void World::render(int resX, int resY, RenderMode mode)
{
	sf::RenderWindow& window = *spWindow;

	Ray r(camera.position, camera.direction);

	for(int x = 0; x < (signed)resX; ++x)
	{
		for(int y = 0; y < (signed)resY; ++y)
		{
			for(auto it = geometry.cbegin(); it != geometry.cend(); ++it)
			{
				r.pos.x = camera.position.x + x - (float)resX * 0.5;//center screen on coordinates
				r.pos.y = camera.position.y + y - (float)resY * 0.5;
				if((**it).intersects(r).init)
					setPixel(x, y);
			}
		}
	}


	window.clear();
	window.draw(sprite);
	window.display();
}
void World::save(const std::string& rName)
{
	image.saveToFile(rName);
}
void World::setPixel(int x, int y, sf::Color c)
{
	if(x < 0 || x >= image.getSize().x || y < 0 || y >= image.getSize().y)
		return;

	image.setPixel(x, y, c);
	texture.loadFromImage(image);
}
void World::addGeometry(sptr<Geometry> spGeo)
{
	geometry.push_back(spGeo);
}
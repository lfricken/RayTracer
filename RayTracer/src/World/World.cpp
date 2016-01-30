#include "World.hpp"

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
void World::render()
{
	sf::RenderWindow& window = *spWindow;

	window.clear();
	window.draw(sprite);
	window.display();
}
void World::save(const std::string& rName)
{
	image.saveToFile(rName);
}
void World::setPixel(unsigned x, unsigned y, sf::Color c)
{
	image.setPixel(x, y, c);
	texture.loadFromImage(image);
}

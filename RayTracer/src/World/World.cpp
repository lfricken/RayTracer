#include "World.hpp"
#include "Ray.hpp"
#include "Geometry.hpp"
#include "Light.hpp"

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
void World::render(int resX, int resY, double perX, double perY, RenderMode mode)
{
	sf::RenderWindow& window = *spWindow;

	Ray r(Vector(0, 0, 0), Vector(1, 0, 0));

	image.create(512, 512, sf::Color(128, 128, 128, 255));

	if(mode == RenderMode::Orthographic)
	{
		for(int x = 0; x < (signed)resX; ++x)
		{
			for(int y = 0; y < (signed)resY; ++y)
			{
				for(auto it = geometry.cbegin(); it != geometry.cend(); ++it)
				{
					r.pos.y = 0 + (x - (float)resX * 0.5)*(perX / resX);//center screen on coordinates
					r.pos.z = 0 + (y - (float)resY * 0.5)*(perY / resY);
					if((**it).intersects(r, *this).init)
						setPixel(x, -y + resY, r.lastColor);
				}
			}
		}
	}
	else if(mode == RenderMode::PerspectivePlane)
	{
		for(int x = 0; x < (signed)resX; ++x)
		{
			for(int y = 0; y < (signed)resY; ++y)
			{
				for(auto it = geometry.cbegin(); it != geometry.cend(); ++it)
				{
					r.pos.y = -(0 + (x - (float)resX * 0.5)*(perX / resX));//center screen on coordinates
					r.pos.z = 0 + (y - (float)resY * 0.5)*(perY / resY);
					r.dir = Vector(-camera.eyedist, 0, 0).to(r.pos).normal();
					if((**it).intersects(r, *this).init)
						setPixel(x, -y + resY, r.lastColor);
				}
			}
		}
	}

	texture.loadFromImage(image);
	window.clear();
	window.draw(sprite);
	window.display();
}
void World::save(const std::string& rName)
{
	texture.loadFromImage(image);
	image.saveToFile(rName);
}
void World::setPixel(int x, int y, sf::Color c)
{
	if(x < 0 || x >= (signed)image.getSize().x || y < 0 || y >= (signed)image.getSize().y)
		return;

	image.setPixel(x, y, c);
}


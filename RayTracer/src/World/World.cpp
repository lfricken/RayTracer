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
void World::render(int resX, int resY, double perX, double perY, RenderMode mode, SampleMode sample)
{
	std::default_random_engine gen;
	gen.seed(time(NULL));
	std::uniform_real_distribution<float> jitter(-0.25, 0.25);

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
					if(sample == SampleMode::PerPixel)
					{
						r.pos.y = 0 + (x - (float)resX * 0.5)*(perX / resX);//center screen on coordinates
						r.pos.z = 0 + (y - (float)resY * 0.5)*(perY / resY);
						if((**it).intersects(r, *this).init)
							setPixel(x, -y + resY, r.lastColor);
					}
					else// MultiJitter
					{
						sf::Color q = sf::Color(64, 64, 64, 64);
						sf::Color d = sf::Color(0, 0, 0, 0);
						sf::Color c1(d), c2(d), c3(d), c4(d);



						r.pos.y = 0 + ((x - 0.25 + jitter(gen)) - (float)resX * 0.5)*(perX / resX);
						r.pos.z = 0 + ((y - 0.25 + jitter(gen)) - (float)resY * 0.5)*(perY / resY);
						bool i1 = (**it).intersects(r, *this).init;
						if(i1)
							c1 = r.lastColor*q;

						r.pos.y = 0 + ((x + 0.25 + jitter(gen)) - (float)resX * 0.5)*(perX / resX);
						r.pos.z = 0 + ((y - 0.25 + jitter(gen)) - (float)resY * 0.5)*(perY / resY);
						bool i2 = (**it).intersects(r, *this).init;
						if(i2)
							c2 = r.lastColor*q;

						r.pos.y = 0 + ((x - 0.25 + jitter(gen)) - (float)resX * 0.5)*(perX / resX);
						r.pos.z = 0 + ((y + 0.25 + jitter(gen)) - (float)resY * 0.5)*(perY / resY);
						bool i3 = (**it).intersects(r, *this).init;
						if(i3)
							c3 = r.lastColor*q;

						r.pos.y = 0 + ((x + 0.25 + jitter(gen)) - (float)resX * 0.5)*(perX / resX);
						r.pos.z = 0 + ((y + 0.25 + jitter(gen)) - (float)resY * 0.5)*(perY / resY);
						bool i4 = (**it).intersects(r, *this).init;
						if(i4)
							c4 = r.lastColor*q;

						//if(!(i1 && i2 && i3 && i4) && (i1 || i2 || i3 || i4))
						//{
						//	i1 = true;
						//}

						sf::Color p = c1 + c2 + c3 + c4;
						if(i1 || i2 || i3 || i4)
						{
							sf::Color back = image.getPixel(x, -y + resY);
							int alpha = 255 - p.a;
							sf::Color mod(alpha, alpha, alpha, alpha);
							sf::Color finalp = p + (back*mod);
							setPixel(x, -y + resY, finalp);
						}
					}
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
					if(sample == SampleMode::PerPixel)
					{
						r.pos.y = -(0 + (x - (float)resX * 0.5)*(perX / resX));//center screen on coordinates
						r.pos.z = 0 + (y - (float)resY * 0.5)*(perY / resY);
					}
					else//else MultiJitter
					{
						r.pos.y = -(0 + (x - (float)resX * 0.5)*(perX / resX));//center screen on coordinates
						r.pos.z = 0 + (y - (float)resY * 0.5)*(perY / resY);
					}

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


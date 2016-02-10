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
/// <summary>
/// Renders the specified resource x.
/// </summary>
/// <param name="resX">The resource x.</param>
/// <param name="resY">The resource y.</param>
/// <param name="perX">The per x.</param>
/// <param name="perY">The per y.</param>
/// <param name="mode">The mode.</param>
/// <param name="sample">The sample.</param>
void World::render(int resX, int resY, double perX, double perY, RenderMode mode, SampleMode sample)
{
	std::default_random_engine gen;
	gen.seed((unsigned long)time(NULL));
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
				if(sample == SampleMode::PerPixel)
				{
					r.pos.y = 0 + (x - (float)resX * 0.5)*(perX / resX);//center screen on coordinates
					r.pos.z = 0 + (y - (float)resY * 0.5)*(perY / resY);
					getFirstHit(r);
					setPixel(-x + resX, -y + resY, r.lastColor);
				}
				else// MultiJitter
				{
					sf::Color d = sf::Color(0, 0, 0, 0);
					sf::Color c1(d), c2(d), c3(d), c4(d);



					r.pos.y = 0 + ((x - 0.25 + jitter(gen)) - (float)resX * 0.5)*(perX / resX);
					r.pos.z = 0 + ((y - 0.25 + jitter(gen)) - (float)resY * 0.5)*(perY / resY);
					getFirstHit(r);
					c1 = r.lastColor;

					r.pos.y = 0 + ((x + 0.25 + jitter(gen)) - (float)resX * 0.5)*(perX / resX);
					r.pos.z = 0 + ((y - 0.25 + jitter(gen)) - (float)resY * 0.5)*(perY / resY);
					getFirstHit(r);
					c2 = r.lastColor;

					r.pos.y = 0 + ((x - 0.25 + jitter(gen)) - (float)resX * 0.5)*(perX / resX);
					r.pos.z = 0 + ((y + 0.25 + jitter(gen)) - (float)resY * 0.5)*(perY / resY);
					getFirstHit(r);
					c3 = r.lastColor;

					r.pos.y = 0 + ((x + 0.25 + jitter(gen)) - (float)resX * 0.5)*(perX / resX);
					r.pos.z = 0 + ((y + 0.25 + jitter(gen)) - (float)resY * 0.5)*(perY / resY);
					getFirstHit(r);
					c4 = r.lastColor;

					int r = c1.r + c2.r + c3.r + c4.r;
					int g = c1.g + c2.g + c3.g + c4.g;
					int b = c1.b + c2.b + c3.b + c4.b;
					int a = c1.a + c2.a + c3.a + c4.a;

					sf::Color p(r / 4, g / 4, b / 4, a / 4);

					sf::Color back = image.getPixel(x, -y + resY);
					int alpha = 255 - p.a;
					sf::Color mod(alpha, alpha, alpha, alpha);
					sf::Color finalp = p + (back*mod);
					setPixel(-x + resX, -y + resY, finalp);
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
				r.lastColor = sf::Color(128, 128, 128, 255);
				if(sample == SampleMode::PerPixel)
				{
					r.pos.y = -(0 + (x - (float)resX * 0.5)*(perX / resX));//center screen on coordinates
					r.pos.z = 0 + (y - (float)resY * 0.5)*(perY / resY);
					r.dir = Vector(-camera.eyedist, 0, 0).to(r.pos).normal();
					getFirstHit(r);
					setPixel(x, -y + resY, r.lastColor);
				}
				else//else MultiJitter
				{
					sf::Color d = sf::Color(0, 0, 0, 0);
					sf::Color c1(d), c2(d), c3(d), c4(d);



					r.pos.y = 0 + ((x - 0.25 + jitter(gen)) - (float)resX * 0.5)*(perX / resX);
					r.pos.z = 0 + ((y - 0.25 + jitter(gen)) - (float)resY * 0.5)*(perY / resY);
					r.dir = Vector(-camera.eyedist, 0, 0).to(r.pos).normal();
					getFirstHit(r);
					c1 = r.lastColor;

					r.pos.y = 0 + ((x + 0.25 + jitter(gen)) - (float)resX * 0.5)*(perX / resX);
					r.pos.z = 0 + ((y - 0.25 + jitter(gen)) - (float)resY * 0.5)*(perY / resY);
					r.dir = Vector(-camera.eyedist, 0, 0).to(r.pos).normal();
					getFirstHit(r);
					c2 = r.lastColor;

					r.pos.y = 0 + ((x - 0.25 + jitter(gen)) - (float)resX * 0.5)*(perX / resX);
					r.pos.z = 0 + ((y + 0.25 + jitter(gen)) - (float)resY * 0.5)*(perY / resY);
					r.dir = Vector(-camera.eyedist, 0, 0).to(r.pos).normal();
					getFirstHit(r);
					c3 = r.lastColor;

					r.pos.y = 0 + ((x + 0.25 + jitter(gen)) - (float)resX * 0.5)*(perX / resX);
					r.pos.z = 0 + ((y + 0.25 + jitter(gen)) - (float)resY * 0.5)*(perY / resY);
					r.dir = Vector(-camera.eyedist, 0, 0).to(r.pos).normal();
					getFirstHit(r);
					c4 = r.lastColor;


					int r = c1.r + c2.r + c3.r + c4.r;
					int g = c1.g + c2.g + c3.g + c4.g;
					int b = c1.b + c2.b + c3.b + c4.b;
					int a = c1.a + c2.a + c3.a + c4.a;

					sf::Color p(r / 4, g / 4, b / 4, a / 4);

					sf::Color back = image.getPixel(x, -y + resY);
					int alpha = 255 - p.a;
					sf::Color mod(alpha, alpha, alpha, alpha);
					sf::Color finalp = p + (back*mod);
					setPixel(-x + resX, -y + resY, finalp);
				}
			}
		}
	}

	texture.loadFromImage(image);
	window.clear();
	window.draw(sprite);
	window.display();
}
/// <summary>
/// Saves image to file
/// </summary>
/// <param name="rName">name of image</param>
void World::save(const std::string& rName)
{
	texture.loadFromImage(image);
	image.saveToFile(rName);
}
/// <summary>
/// Sets the pixel on the image
/// </summary>
/// <param name="x">x position</param>
/// <param name="y">y position</param>
/// <param name="c">color</param>
void World::setPixel(int x, int y, sf::Color c)
{
	if(x < 0 || x >= (signed)image.getSize().x || y < 0 || y >= (signed)image.getSize().y)
		return;

	image.setPixel(x, y, c);
}
/// <summary>
/// finds the first hit position for this ray
/// </summary>
/// <param name="ray">The ray.</param>
void World::getFirstHit(Ray& ray) const
{
	sf::Color lastColor(128, 128, 128, 255);
	double lastTime = -1;
	for(auto it = geometry.cbegin(); it != geometry.cend(); ++it)
	{
		if((**it).intersects(ray, *this).init)//we hit this object
		{
			if(lastTime == -1 || lastTime > ray.time)
			{
				lastColor = ray.lastColor;
				lastTime = ray.time;
			}

		}
	}
	ray.lastColor = lastColor;
	ray.time = lastTime;
}

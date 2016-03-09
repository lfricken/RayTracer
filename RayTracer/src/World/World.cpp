#include "World.hpp"
#include "Ray.hpp"
#include "Geometry.hpp"
#include "Light.hpp"

using namespace std;
using namespace leon;

World::World()
{
	spWindow = sptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(400, 400), "Leon's Ray Tracer: 2016 Edition"));
	image.create(400, 400, sf::Color(128, 128, 128, 255));
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
void World::render(int resX, int resY, double perX, double perY, RenderMode mode, SampleMode sample, int samples)
{
	std::default_random_engine gen;
	gen.seed((unsigned long)time(NULL));
	std::uniform_int_distribution<unsigned int> rooks;

	vector<int> row;
	vector<int> column;
	for(int i = 1; i <= samples; ++i)
	{
		row.push_back(i);
		column.push_back(i);
	}


	double xMod = -((float)resX * 0.5)*(perX / resX);
	double yMod = -((float)resY * 0.5)*(perY / perY);

	sf::RenderWindow& window = *spWindow;

	Ray ray(Vector(0, 0, 0), Vector(1, 0, 0));

	image.create(420, 420, sf::Color(128, 128, 128, 255));

	if(mode == RenderMode::Orthographic)
	{
		for(int x = 0; x < (signed)resX; ++x)
		{
			for(int y = 0; y < (signed)resY; ++y)
			{
				if(sample == SampleMode::PerPixel)
				{
					ray.pos.y = 0 + (x - (float)resX * 0.5)*(perX / resX);//center screen on coordinates
					ray.pos.z = 0 + (y - (float)resY * 0.5)*(perY / resY);
					getFirstHit(ray);
					setPixel(-x + resX, -y + resY, ray.lastColor);
				}
				else// MultiJitter
				{
					sf::Color c1;
					int r = 0, g = 0, b = 0, a = 0;
					auto row2 = row;
					auto column2 = column;

					for(int sample = 0; sample < samples; ++sample)
					{
						std::uniform_int_distribution<unsigned int>::param_type range(0, samples - (sample+1));
						rooks.param(range);
						int xIndex = rooks(gen);
						int yIndex = rooks(gen);
						//Convert them to a coordinate addition

						double offsetX = (static_cast<double>(column2[xIndex]) - ((samples / 2.0) + 0.5))/samples;
						double offsetY = (static_cast<double>(row2[yIndex]) - ((samples / 2.0) + 0.5))/samples;

						column2.erase(column2.begin() + xIndex);
						row2.erase(row2.begin() + yIndex);


						//cast the ray to get the color
						ray.pos.y = 0 + (x + offsetX - (float)resX * 0.5)*(perX / resX);
						ray.pos.z = 0 + (y + offsetY - (float)resY * 0.5)*(perY / resY);
						getFirstHit(ray);
						c1 = ray.lastColor;

						//add color to total rgba
						r += c1.r;
						g += c1.g;
						b += c1.b;
					}

					sf::Color finalColor(r / samples, g / samples, b / samples);
					setPixel(-x + resX, -y + resY, finalColor);
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
				ray.lastColor = sf::Color(128, 128, 128, 255);
				if(sample == SampleMode::PerPixel)
				{
					ray.pos.y = -(0 + (x - (float)resX * 0.5)*(perX / resX));//center screen on coordinates
					ray.pos.z = 0 + (y - (float)resY * 0.5)*(perY / resY);
					ray.dir = Vector(-camera.eyedist, 0, 0).to(ray.pos).normal();
					getFirstHit(ray);
					setPixel(x, -y + resY, ray.lastColor);
				}
				else// MultiJitter
				{
					sf::Color c1;
					int r = 0, g = 0, b = 0, a = 0;
					auto row2 = row;
					auto column2 = column;

					for(int sample = 0; sample < samples; ++sample)
					{
						std::uniform_int_distribution<unsigned int>::param_type range(0, samples - (sample + 1));
						rooks.param(range);
						int xIndex = rooks(gen);
						int yIndex = rooks(gen);
						//Convert them to a coordinate addition

						double offsetX = (static_cast<double>(column2[xIndex]) - ((samples / 2.0) + 0.5)) / samples;
						double offsetY = (static_cast<double>(row2[yIndex]) - ((samples / 2.0) + 0.5)) / samples;

						column2.erase(column2.begin() + xIndex);
						row2.erase(row2.begin() + yIndex);


						//cast the ray to get the color
						ray.pos.y = 0 + (x + offsetX - (float)resX * 0.5)*(perX / resX);
						ray.pos.z = 0 + (y + offsetY - (float)resY * 0.5)*(perY / resY);
						ray.dir = Vector(-camera.eyedist, 0, 0).to(ray.pos).normal();
						getFirstHit(ray);
						c1 = ray.lastColor;

						//add color to total rgba
						r += c1.r;
						g += c1.g;
						b += c1.b;
					}

					sf::Color finalColor(r / samples, g / samples, b / samples);
					setPixel(-x + resX, -y + resY, finalColor);
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

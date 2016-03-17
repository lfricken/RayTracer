#include "World.hpp"
#include "Ray.hpp"
#include "Geometry.hpp"
#include "Light.hpp"
#include "Triangle.hpp"
#include <fstream>

using namespace std;
using namespace leon;

World::World()
{
	octree.reset(new OctTree(Vector(0, 0, 0), 2048, 2, 1));
	spWindow = sptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(400, 400), "Leon's Ray Tracer: 2016 Edition"));
	image.create(400, 400, backgroundColor);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}
World::~World()
{

}
void World::loadModel(double scale, const std::string& fileName, const Vector& position)//load a model into the world
{
	std::string dir = content + "models/" + fileName;
	//Note: Obj files index at 1, not 0
	vector<Vector> verts;
	verts.push_back(Vector(-1, -1, -1));

	ifstream inFile(dir);

	string line;
	bool done = false;
	while(!done && getline(inFile, line))//std::getline(infile, line))
	{
		if(line[0] == 'v')//vertex
		{
			line.erase(line.begin(), line.begin() + 1);
			double x, y, z;
			istringstream iss(line);
			if(iss >> x >> y >> z)
				verts.push_back(position + Vector(x * scale, y * scale, z * scale));
			else
				perror("AAA");
			//cout << "\n" << x << "\t" << y << "\t" << z;
		}
		else if(line[0] == 'f')//face
		{
			line.erase(line.begin(), line.begin() + 1);
			int v1, v2, v3;
			istringstream iss(line);
			if(iss >> v1 >> v2 >> v3)
				this->add(new Triangle(verts[v1], verts[v2], verts[v3]));
			else
				perror("AAA");
			//cout << "\n" << v1 << "\t" << v2 << "\t" << v3;
		}
		else
		{
			perror(line.c_str());
		}
	}

}
void World::add(Geometry* geo)
{
	geometry.push_back(sptr<Geometry>(geo));
	octree->addObject(geometry.back().get());
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


	double xMod = -((double)resX * 0.5)*(perX / resX);
	double yMod = -((double)resY * 0.5)*(perY / perY);

	sf::RenderWindow& window = *spWindow;

	Ray ray(Vector(0, 0, 0), Vector(1, 0, 0));

	image.create(420, 420, backgroundColor);

	if(mode == RenderMode::Orthographic)
	{
		for(int x = 0; x < (signed)resX; ++x)
		{
			cout << "\n" << (x * 100) / resX << "%";
			for(int y = 0; y < (signed)resY; ++y)
			{
				if(sample == SampleMode::PerPixel)
				{
					ray.pos.y = 0 + (x - (double)resX * 0.5)*(perX / resX);//center screen on coordinates
					ray.pos.z = 0 + (y - (double)resY * 0.5)*(perY / resY);
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
						ray.pos.y = 0 + (x + offsetX - (double)resX * 0.5)*(perX / resX);
						ray.pos.z = 0 + (y + offsetY - (double)resY * 0.5)*(perY / resY);
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
			cout << "\n" << (x * 100) / resX << "%";
			for(int y = 0; y < (signed)resY; ++y)
			{
				ray.lastColor = backgroundColor;
				if(sample == SampleMode::PerPixel)
				{
					ray.pos.y = -(0 + (x - (double)resX * 0.5)*(perX / resX));//center screen on coordinates
					ray.pos.z = 0 + (y - (double)resY * 0.5)*(perY / resY);
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
						ray.pos.y = 0 + (x + offsetX - (double)resX * 0.5)*(perX / resX);
						ray.pos.z = 0 + (y + offsetY - (double)resY * 0.5)*(perY / resY);
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
	{
		cout << "\nIndex Error!";
		return;
	}

	image.setPixel(x, y, c);
}
/// <summary>
/// finds the first hit position for this ray
/// </summary>
/// <param name="ray">The ray.</param>
void World::getFirstHit(Ray& ray) const
{
	std::set<const Geometry*> candidates = octree->getCandidates(ray);

	ray.lastHit = NULL;
	const Geometry* last = NULL;

	double lastTime = -1;
	for(auto it = candidates.cbegin(); it != candidates.cend(); ++it)
	{
		if((**it).intersects(ray, *this).init)//we hit this object
		{
			if(lastTime == -1 || lastTime > ray.time)
			{
				last = ray.lastHit;
				lastTime = ray.time;
			}

		}
	}

	if(last != NULL)
		ray.lastColor = last->getColorPoint(ray.pos + ray.dir * lastTime, *this);
	else
		ray.lastColor = backgroundColor;



	ray.time = lastTime;
}

#pragma once

#include "stdafx.hpp"
#include "Camera.hpp"

namespace leon
{
	enum class RenderMode
	{
		Orthographic,
		PerspectivePlane,
	};
	enum class SampleMode
	{
		PerPixel,
		MultiJitter,
	};

	class Ray;
	class Geometry;
	class Light;
	class World
	{
	public:
		World();
		virtual ~World();

		void setPixel(int x, int y = 0, sf::Color c = sf::Color::Blue);
		void save(const std::string& rName);

		void render(int resX, int resY, double perX, double perY, RenderMode mode = RenderMode::PerspectivePlane, SampleMode sample = SampleMode::PerPixel, int samples = 2);

		Camera camera;

		vector<sptr<Geometry> > geometry;
		vector<sptr<Light> > lights;

		const sf::Color backgroundColor = sf::Color(0, 0, 0);
		const sf::Color ambientLight = sf::Color(15, 15, 15);

		void getFirstHit(Ray& ray) const;

	protected:
	private:


		sptr<sf::RenderWindow> spWindow;

		sf::Texture texture;
		sf::Image image;
		sf::Sprite sprite;

	};
}



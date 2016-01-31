#pragma once

#include "stdafx.hpp"
#include "Geometry.hpp"
#include "Camera.hpp"

namespace leon
{
	enum class RenderMode
	{
		Orthographic,
	};

	class World
	{
	public:
		World();
		virtual ~World();

		void setPixel(int x, int y = 0, sf::Color c = sf::Color::Blue);
		void save(const std::string& rName);

		void render(int resX, int resY, RenderMode mode);

		void addGeometry(sptr<Geometry> spGeo);

		Camera camera;

	protected:
	private:
		vector<sptr<Geometry> > geometry;

		sptr<sf::RenderWindow> spWindow;

		sf::Texture texture;
		sf::Image image;
		sf::Sprite sprite;

	};
}
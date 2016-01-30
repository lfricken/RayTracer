#pragma once

#include "stdafx.hpp"

namespace leon
{
	class World
	{
	public:
		World();
		virtual ~World();

		void setPixel(unsigned x, unsigned y = 0, sf::Color c = sf::Color::Blue);
		void save(const std::string& rName);

		void render();

	protected:
	private:
		sptr<sf::RenderWindow> spWindow;

		sf::Texture texture;
		sf::Image image;
		sf::Sprite sprite;

	};
}
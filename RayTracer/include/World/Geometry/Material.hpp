#pragma once
#include "stdafx.hpp"

struct Material
{
	Material()
	{
		color = sf::Color::White;
		specular = 1.f;
		diffuse = 1.f;
		reflection = 0.f;
	}

	sf::Color color;
	float specular;//between 0 and 1
	float diffuse;//between 0 and 1
	float reflection;//between 0 and 1
};




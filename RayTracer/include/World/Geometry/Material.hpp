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
		gloss = 0.f;
		transparency = 0.f;
		indexRefraction = 1.0f;

		glossRootDimensions = 0.2;
		glossRootSamples = 2;
	}

	sf::Color color;
	float specular;//between 0 and 1
	float diffuse;//between 0 and 1
	float reflection;//between 0 and 1
	float gloss;//between 0 and 1
	float transparency;//between 0 and 1
	float indexRefraction;//between 1 and 3

	float glossRootDimensions;//recommended between 0.1 and 5
	int glossRootSamples;//recommended between 1 and 3


};




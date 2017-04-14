#pragma once
#include <SFML/Graphics.hpp>
#include "libs/map.h"

using namespace sf;

sf::View view;
double bgX = 0, bgY = 0;

void setPlayerCoordinateForView(double x, double y)
{
	double tempX = x; double tempY = y;

	if (x < 400 * 8 / 10) tempX = 400 * 8 / 10;
	if (y < 300 * 8 / 10) tempY = 300 * 8 / 10;
	if (y > HEIGHT_MAP * 32 - 300 * 8 / 10) tempY = HEIGHT_MAP * 32 - 300 * 8 / 10;
	if (x > WIDTH_MAP * 32 - 400 * 8 / 10) tempX = WIDTH_MAP * 32 - 400 * 8 / 10;

	view.setCenter((float)tempX, (float)tempY);
}

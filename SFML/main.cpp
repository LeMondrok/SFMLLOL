#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "libs/gameengine.h"

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(800, 600), "");;;

    view.reset(FloatRect(0, 0, 800, 600));

    Clock clock;

    gameLoop lol (&window, 0);


    while (window.isOpen())
    {
		double time = (double)clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

        Event event;

        while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		lol.update(time);
    }
}

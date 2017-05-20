#pragma once
#include "libs/draw.h"
#include "libs/Entity.h"
#include "libs/Player.h"
#include "libs/Enemy.h"
#include <list>

using namespace sf;

class gameLoop
{
public:
    std::list <Entity*> entities;
	std::vector <std::list<Entity*>::iterator> QueryDeath;
    Sprite s_map;
    Image map_image;
    Texture map;

    Player *player;

    Sprite Sbg;
    Image Ibg;
    Texture Tbg;

    gameLoop (RenderWindow *Window, bool choose)
    {
        window = Window;

        map_image.loadFromFile("images/8246060_orig.jpg");

        map.loadFromImage(map_image);

        s_map.setTexture(map);

        Image heroImage;
        heroImage.loadFromFile("images/Безымянный.png");
        Image diabloImage;
        diabloImage.loadFromFile ("images/UnicornSprite.png");

        player = new Player(&heroImage, 200, 200, 45, 100, &entities, &QueryDeath);

        Unicorn *E;
        E = new Unicorn (&diabloImage, 750, 500, &entities, &QueryDeath);

        entities.push_back (player);
        entities.push_back (E);

        Ibg.loadFromFile("images/bg2.png");
        Tbg.loadFromImage(Ibg);
        Sbg.setTexture(Tbg);

        view.zoom((float)0.8);
    }

    void update(double time)
    {
		for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
			if (entIsAlive[(*it)->num])
				(*it)->update(time);

		
		draw(window, &s_map, &entities, time, player, Sbg);

		for (int i = QueryDeath.size() - 1; i >= 0; i--)
		{
			(*QueryDeath[i])->del();

			entities.erase(QueryDeath[i]);
		}

		QueryDeath.clear();

		return;
     }


private:
    RenderWindow *window;
};

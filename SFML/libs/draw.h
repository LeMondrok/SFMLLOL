#pragma once
#include <SFML/Graphics.hpp>
#include "libs/map.h"
#include "libs/Entity.h"
#include "libs/Player.h"
#include "libs/Enemy.h"
#include <iostream>
#include <list>

double xBg = 0, yBg = 0;

void setBg(double x, double y);

void drawMap (sf::RenderWindow *window, Sprite *s_map)
{
    for (int i = 0; i < HEIGHT_MAP; i++)
        for (int j = 0; j < WIDTH_MAP; j++)
        {
            if (TileMap[i][j] != ' ')
            {
                if (TileMap[i][j] == 's')  s_map->setTextureRect(IntRect(32, 0, 32, 32));
                if ((TileMap[i][j] == '0')) s_map->setTextureRect(IntRect(73, 7, 32, 32));
                if ((TileMap[i][j] == 'f')) s_map->setTextureRect(IntRect(73, 40, 32, 32));
                if ((TileMap[i][j] == 'h')) s_map->setTextureRect(IntRect(277, 22, 32, 16));
                s_map->setPosition((float)j * 32, (float)i * 32);

                window->draw(*s_map);
            }
        }
}

void drawEntities (sf::RenderWindow *window, std::list <Entity*> *enemies, double time)
{
    std::list<Entity*>::iterator it;

    for (it = enemies->begin(); it != enemies->end(); it++)
        if(entIsAlive[(*it)->num])(*it)->drawE(time, window);
}

void draw(sf::RenderWindow *window, Sprite *s_map, std::list <Entity*> *enemies, double time, Player *p, sf::Sprite Sbg)
{
    window->setView(view);
    window->clear();

    setBg(p->x, p->y);

    Sbg.setPosition((float)xBg, (float)yBg);

    window->draw(Sbg);

    drawMap (window, s_map);
    drawEntities(window, enemies, time);

    window->display();
}

void setBg(double x, double y)
{
	double tX = 0, tY = 0;

    tX = (WIDTH_MAP * 32 - 1000) / 2 + (x - WIDTH_MAP  * 32 / 2) * (WIDTH_MAP  * 32 / 2 - 400) / (WIDTH_MAP  * 32 / 2 - 400 * 8 / 10);
    tY = (HEIGHT_MAP * 32 - 580) / 2 + (y - HEIGHT_MAP * 32 / 2) * (HEIGHT_MAP * 32 / 2 - 300) / (HEIGHT_MAP * 32 / 2 - 300 * 8 / 10);

    if (x < 400 * 8 / 10) tX = (WIDTH_MAP * 32 - 1000) / 2 + (400 * 8 / 10 - WIDTH_MAP  * 32 / 2) * (WIDTH_MAP  * 32 / 2 - 400) / (WIDTH_MAP  * 32 / 2 - 400 * 8 / 10);
	if (y < 300 * 8 / 10) tY = (HEIGHT_MAP * 32 - 580) / 2 + (300 * 8 / 10 - HEIGHT_MAP * 32 / 2) * (HEIGHT_MAP * 32 / 2 - 300) / (HEIGHT_MAP * 32 / 2 - 300 * 8 / 10);
	if (y > HEIGHT_MAP * 32 - 300 * 8 / 10) tY = (HEIGHT_MAP * 32 - 580) / 2 + (HEIGHT_MAP * 32 - 300 * 8 / 10 - HEIGHT_MAP * 32 / 2) * (HEIGHT_MAP * 32 / 2 - 300) / (HEIGHT_MAP * 32 / 2 - 300 * 8 / 10);
	if (x > WIDTH_MAP * 32 - 400 * 8 / 10) tX = (WIDTH_MAP * 32 - 1000) / 2 + (WIDTH_MAP * 32 - 400 * 8 / 10 - WIDTH_MAP  * 32 / 2) * (WIDTH_MAP  * 32 / 2 - 400) / (WIDTH_MAP  * 32 / 2 - 400 * 8 / 10);

    xBg = tX, yBg = tY;
}

#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <libs/map.h>
#include <libs/view.h>
#include <list>
#include <vector>
#include <libs/notmy/collision/Collision.h>
//#include <libs/Animation.h>

unsigned int ident = 0, enemyCount = 0;
std::vector <bool> entIsAlive;

class Entity
{
public:
	double vx, vy, x, y, speed;
    int health, w, h;
    bool onGround;
    unsigned int num;
	std::list <Entity*> *l;
	std::vector < std::list<Entity*>::iterator > *Qd;

    enum { fr, unfr, frbul, unfrbul, spawner, portal, died} type;

    sf::Texture texture;
	sf::Sprite sprite;

	Entity(sf::Image *image, double X, double Y, int W, int H, std::list <Entity*> *L, std::vector < std::list<Entity*>::iterator > *QD)
    {
		l = L;
		Qd = QD;

        num = ident;
        entIsAlive.push_back (1);
        ident++;
        x = X;
        y = Y;
        w = W;
        h = H;

        speed = 0;

        vx = 0;
        vy = 0;

        texture.loadFromImage(*image);
        sprite.setTexture (texture);
        sprite.setOrigin((float)w / 2, (float)h / 2);
    }

	double getX ()
    {
        return x;
    }

	double getY ()
    {
        return y;
    }

    FloatRect getRekt()
    {
		return FloatRect((float)x, (float)y, (float)w, (float)h);
	}

    virtual void update(double time) = 0;

    virtual void drawE (double time, RenderWindow* window) = 0;

	void del()
	{
		for (std::list<Entity*>::iterator Pointer = l->begin(); Pointer != l->end(); Pointer++)
			if ((*Pointer)->num == num)
			{
				entIsAlive[num] = 0;

				Qd->push_back(Pointer);

				this->type = died;

				return;
			}
	}
};

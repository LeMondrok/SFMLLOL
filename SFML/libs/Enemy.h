#pragma once
#include "libs/Entity.h"

class Enemy :
    public Entity
{
    public:
    enum { stay, up, right, down, left, jump} state;
	double timer;

    Enemy(Image *image, double X, double Y, int W, int H, std::list <Entity*> *l, std::vector < std::list<Entity*>::iterator > *Qd)
    : Entity(image, X, Y, W, H, l, Qd)
    {
        enemyCount++;

        type = unfr;

        state = stay;
        timer = 0;
    }

    virtual void update(double time) = 0;

    void drawE (double time, RenderWindow* window);

    bool checkCol(double Vx, double Vy);

    virtual void AI (double *timer) = 0;

    void dead();
};

void Enemy::drawE (double time, RenderWindow* window)
{
    window->draw (sprite);
}

void Enemy::dead ()
{
    this->del();

    return;
}

bool Enemy::checkCol(double Vx, double Vy)
{
    for (int i = (int)(y / 32); i < (y + h) / 32; i++)
        for (int j = (int)(x / 32); j < (x + w) / 32; j++)
        {
           if (TileMap[i][j] == '0' || TileMap[i][j] == 'f')
           {
                if (Vy > 0)
                {
                    y = i * 32 - h;
                    vy = 0;
                    onGround = true;
                }

                if (Vy < 0)
                {
                    y = i * 32 + 32;
                    vy = 0;
                }

                if (Vx > 0)
                {
                    x = j * 32 - w;
                }

                if (Vx < 0)
                {
                    x = j * 32 + 32;
                }
           }
       }

    return 0;
}

class Diablo : public Enemy
{
public:
    bool seeHero = 0;

	double pX = 0, pY = 0, timerSee = 0;

    Diablo (Image *image, double X, double Y, std::list <Entity*> *l, std::vector < std::list<Entity*>::iterator > *Qd)
    : Enemy (image, X, Y, 54, 103, l, Qd)
    {
        health = 10;

        sprite.setTextureRect(IntRect(0, 0, w, h));
    }

private:
    Image enemyImage;
    void update (double time);
    void AI (double *timer);
};

void Diablo::update (double time)
{
    if (health <= 0)
    {
        this->dead();
        return;
    }

    timer += time;
    timerSee += time;

    AI(&timer);

    pX = x;

    switch (state)
    {
        case right : vx =  speed; sprite.setScale(-1, 1); break;
        case left  : vx = -speed; sprite.setScale( 1, 1); break;
        case up    :              break;
        case down  : vx = 0;      break;
        case stay  :              break;
    }

    x += vx * time;
    if (checkCol(vx, 0) == 1) return;

    y += vy * time;
    if (checkCol(0, vy) == 1) return;

    vy +=  0.0015 * time;

    sprite.setPosition((float)(x + w / 2), (float)(y + h / 2));
}

void Diablo::AI (double *timer)
{
    std::list<Entity*>::iterator b = l->begin();

    if (fabs ((*b)->y - this->y) < (*b)->h + this->h && fabs ((*b)->x - this->x) < 640 / 2)
    {
        timerSee = 0;

        seeHero = 1;
    }

    if (timerSee > 500)
        seeHero = 0;

    if (!seeHero)
    {
        if (*timer > 10000)
        {
            *timer = 0;
        }

        if (*timer > 5000)
        {
            state = left;
            speed = 0.1;
        }
        else
        {
            state = right;
            speed = 0.1;
        }
        if (pX == x)
            *timer += 5000;
    }
    else
    {
        if ((*b)->x > this->x)
        {
            state = right;
            speed = 0.1;
        }
        else
        {
            state = left;
            speed = 0.1;
        }

        if (onGround && pX == x)
        {
            this->vy = -0.6;
            onGround = 0;
        }
    }
}

class Unicorn : public Enemy
{
public:
    bool seeHero = 0;
	double pX = 0, pY = 0, timerSee = 0;

    //std::list <Weapon*> weapons;

	Lasergun *z;

    Unicorn (Image *image, double X, double Y, std::list <Entity*> *l, std::vector < std::list<Entity*>::iterator > *Qd)
    : Enemy (image, X, Y, 68, 65, l, Qd)
    {
        health = 10;

        sprite.setTextureRect(IntRect(0, 0, w, h));

        z = new Lasergun (8, 0, l, Qd, this);

        //weaponspush_back (z);
    }

    Image enemyImage;
    void update (double time);

private:
    void AI (double *timer);
};

void Unicorn::update (double time)
{
    if (health <= 0)
    {
		std::cout << 5;

        delete z;

        this->dead();

        return;
    }

    timer += time;
    timerSee += time;

    AI(&timer);

    pX = x;

    switch (state)
    {
        case right : vx =  speed; sprite.setScale(-1, 1); break;
        case left  : vx = -speed; sprite.setScale( 1, 1); break;
        case up    :              break;
        case down  : vx = 0;      break;
        case stay  :              break;
    }

    x += vx * time;
    if (checkCol(vx, 0) == 1) return;

    y += vy * time;
    if (checkCol(0, vy) == 1) return;

    vy +=  0.0015 * time;

    sprite.setPosition((float)(x + w / 2), (float)(y + h / 2));

    z->update(time);
}

void Unicorn::AI (double *timer)
{
    std::list<Entity*>::iterator b = l->begin();

    if (fabs ((*b)->y - this->y) < (*b)->h + this->h && fabs ((*b)->x - this->x) < 640 / 2)
    {
        timerSee = 0;

        seeHero = 1;
    }

    if (timerSee > 500)
        seeHero = 0;

    if (!seeHero)
    {
        if (*timer > 10000)
        {
            *timer = 0;
        }

        if (*timer > 5000)
        {
            state = left;
            speed = 0.1;
        }
        else
        {
            state = right;
            speed = 0.1;
        }
        if (pX == x)
            *timer += 5000;
    }
    else
    {
        if (vx > 0)
        {
            z->shoot(1,  &x, &y);
        }
        else
            z->shoot(-1, &x, &y);

        if ((*b)->x > this->x + 100)
        {
            state = right;
            speed = 0.1;
        }
        else
		if ((*b)->x < this->x - 100)
        {
            state = left;
            speed = 0.1;
        }
		else
		{
			speed = 0;
		}

        if (onGround && pX == x)
        {
            this->vy = -0.6;
            onGround = 0;
        }
    }
}


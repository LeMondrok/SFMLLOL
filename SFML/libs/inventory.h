#pragma once
#include <SFML/Graphics.hpp>
#include "libs/Entity.h"
#include "libs/Player.h"

class Explosion :
    public Entity
{
public:
	double timer;

    bool friendly;

    Explosion (Image *image, double X, double Y, int W, int H, int Timer, int damage, 
			   bool Friendly, std::list<Entity*> *l, std::vector < std::list<Entity*>::iterator > *Qd)
    : Entity(image, X, Y, W, H, l, Qd)
    {
        friendly = Friendly;

        sprite.setTextureRect(IntRect(0, 0, w, h));

        sprite.scale (5, 5);
        w *= 5;
        x -= w / 2;
        h *= 5;
        y -= h / 2;

        timer = Timer;

        type = portal;

        for (std::list<Entity*>::iterator b = l->begin(); b != l->end(); b++)
        {
            if (friendly)
            {
                if ((*b)->num != this->num && (*b)->type == unfr && (*b)->getRekt().intersects(this->getRekt()))
                {
                    (*b)->health -= damage;
                }
            }
            else
            {
                if ((*b)->num != this->num && (*b)->type == fr && (*b)->getRekt().intersects(this->getRekt()))
                {
                    (*b)->health -= damage;
                }
            }
        }
    }

    void drawE (double time, RenderWindow* window);

    void update(double time);
};

void Explosion::drawE (double time, RenderWindow* window)
{
    window->draw (sprite);
}

void Explosion::update(double time)
{
    timer -= time;

    if (timer < 0)
        this->del();
    else
        sprite.setPosition((float)(x + w / 2), (float)(y + h / 2));
}

class Rocket :
    public Entity
{
public:
	double ax, ay, sx, sy;

	double range;

	double timer;

    Image *b;

    bool friendly;

    Rocket(Image *image, double X, double Y, int W, int H, double Ax, double Ay, int Range, Image *B, bool Friendly,
		std::list<Entity*> *l, std::vector < std::list<Entity*>::iterator > *Qd)//, state dir)
    : Entity(image, X, Y, W, H, l, Qd)
    {
        friendly = Friendly;

        type = frbul;
        range = Range;

        sx = x;
        sy = y;

        ax = Ax;
        ay = Ay;

        vx = 0;
        vy = 0;

        sprite.setTextureRect(IntRect(0, 0, w, h));
        if (ax < 0) sprite.setScale(-1, 1);

        b = B;
    }

    void update(double time);
    void boom();

    void drawE (double time, RenderWindow* window);

private:
    bool checkCol(double Vx, double Vy);
};

void Rocket::drawE (double time, RenderWindow* window)
{
    window->draw (sprite);
}

void Rocket::update(double time)
{
    timer += time;

    for (std::list<Entity*>::iterator b = l->begin(); b != l->end(); b++)
    {
        if (friendly)
            if ((*b)->num != this->num && (*b)->type == unfr &&(*b)->getRekt().intersects(this->getRekt()))
            {
                this->boom();

                return;
            }
        else
            if ((*b)->num != this->num && (*b)->type == fr &&(*b)->getRekt().intersects(this->getRekt()))
            {
                this->boom();

                return;
            }
    }

    x += vx * time;
    if (checkCol(vx, 0) == 1) return;

    vx += ax * time;

    sprite.setPosition((float)(x + w / 2), (float)(y + h / 2));

    if (vx >= 1)vx = 1;
}

void Rocket::boom()
{
    Explosion *E;

    E = new  Explosion(b, x, y, 32, 28, 1000, 5, friendly, l, Qd);

    l->push_back(E);

    this->del();
}

bool Rocket::checkCol(double Vx, double Vy)
{
    for (int i = (int)(y / 32); i < (y + h) / 32; i++)
        for (int j = (int)(x / 32); j < (x + w) / 32; j++)
        {
           if (TileMap[i][j] == '0' || TileMap[i][j] == 'f')
           {
                this->boom();

                return 1;
           }
        }

    return 0;
}

class Podushka :
    public Entity
{
public:
	double ax, ay, sx, sy;

	double range;

	double timer;

    Image *b;

    bool friendly;

    Podushka(Image *image, double X, double Y, int W, int H, double Vx, double Ay, int Range, Image *B, bool Friendly,
		     std::list <Entity*> *l, std::vector < std::list<Entity*>::iterator > *Qd)
    : Entity(image, X, Y, W, H, l, Qd)
    {
        friendly = Friendly;

        type = frbul;
        range = Range;

        sx = x;
        sy = y;

        ax = 0;
        ay = Ay;

        vx = Vx;
        vy = -0.3;

        sprite.setTextureRect(IntRect(0, 0, w, h));
        if (ax < 0) sprite.setScale(-1, 1);

        b = B;
    }

    void update(double time);
    void boom();

    void drawE (double time, RenderWindow* window);

private:
    bool checkCol(double Vx, double Vy);
};

void Podushka::drawE (double time, RenderWindow* window)
{
    window->draw (sprite);
}

void Podushka::update(double time)
{
    timer += time;

    for (std::list<Entity*>::iterator b = l->begin(); b != l->end(); b++)
    {
        if (friendly)
        {
            if ((*b)->num != this->num && (*b)->type == unfr &&(*b)->getRekt().intersects(this->getRekt()))
            {
                std::cout << friendly;
                this->boom();

                return;
            }
        }
        else
        {
            if ((*b)->num != this->num && (*b)->type == fr &&(*b)->getRekt().intersects(this->getRekt()))
            {
                this->boom();

                return;
            }
        }
    }

    x += vx * time;
    if (checkCol(vx, 0) == 1) return;

    y += vy * time;
    if (checkCol(0, vy) == 1) return;

    vy += ay * time;

    sprite.rotate((float)(1 * time));

    sprite.setPosition((float)(x + w / 2), (float)(y + h / 2));

    if (vx >= 1)vx = 1;
}

void Podushka::boom()
{
    Explosion *E;

    E = new  Explosion(b, x, y, 32, 28, 1000, 5, friendly, l, Qd);

    l->push_back(E);

    this->del();
}

bool Podushka::checkCol(double Vx, double Vy)
{
    for (int i = (int)(y / 32); i < (y + h) / 32; i++)
        for (int j = (int)(x / 32); j < (x + w) / 32; j++)
        {
           if (TileMap[i][j] == '0' || TileMap[i][j] == 'f')
           {
                this->boom();

                return 1;
           }
        }

    return 0;
}

class Weapon
{
public:
	double timer;

	double reload;

    bool load;

    bool friendly;

    int ammo, magazine;

	std::list <Entity*> *l;
	std::vector < std::list<Entity*>::iterator > *Qd;
	Entity* owner;

    Weapon (int Ammo, bool Friendly, std::list <Entity*> *L, std::vector < std::list<Entity*>::iterator > *QD,
			Entity* Owner)
    {
		l = L;

		Qd = QD;

		owner = Owner;

        ammo = Ammo;

        friendly = Friendly;
    }

    virtual void update(double time) = 0;

    virtual void shoot(int dir, double *x, double *y) = 0;
};

class PodushkaMet :
    public Weapon
{
    public:
    bool processing;

    Image i, b;

	double vB = 0.4;

    PodushkaMet (int Ammo, bool Friendly, std::list <Entity*> *l, std::vector < std::list<Entity*>::iterator > *Qd,
				 Entity* Owner)
    : Weapon (Ammo, Friendly, l, Qd, Owner)
    {
        i.loadFromFile("images/kot.png");
        b.loadFromFile("images/boom.png");

        processing = 0;

        magazine = 1;

        reload = 1;
    }

    void update(double time)
    {
        timer += time;

        if (load == 0 && timer >= 1000) load = 1;
    }

    void shoot(int dir, double *x, double *y)
    {
        if (load && processing == 0)
        {
            processing = 1;

            Podushka *r;

            r = new Podushka (&i, *x, *y, 80, 60, (*owner).vx + vB * dir, 0.001, 5, &b, friendly, l, Qd);

			std::cout << 1;

            l->push_back(r);

            load = 0;
            timer = 0;

            processing = 0;
        }
    }
};

class Bazooka :
    public Weapon
{
public:
    bool processing;

    Image i, b;

    Bazooka (int Ammo, bool Friendly, std::list <Entity*> *l, std::vector < std::list<Entity*>::iterator > *Qd,
			 Entity* Owner)
    : Weapon (Ammo, friendly, l, Qd, Owner)
    {
        i.loadFromFile("images/Podushka.png");
        b.loadFromFile("images/boom.png");

        processing = 0;

        magazine = 1;

        reload = 1;
    }

    void update(double time)
    {
        timer += time;

        if (load == 0 && timer >= 1000) load = 1;
    }

    void shoot(int dir, double *x, double *y)
    {
        if (load && processing == 0)
        {
            processing = 1;

            Rocket *r;

            r = new Rocket (&i, *x, *y, 38, 25,  0.001 * dir, 0, 5, &b, friendly, l, Qd);

            l->push_back (r);

            load = 0;
            timer = 0;

            processing = 0;
        }
    }
};

class Laser :
    public Entity
{
public:
	double ax, ay, sx, sy;

	double range;

	double timer;

    Image *b;

    bool friendly;

    Laser(Image *image, double X, double Y, int W, int H, double Vx, double Ay, int Range, Image *B, bool Friendly,
		  std::list <Entity*> *l, std::vector < std::list<Entity*>::iterator > *Qd)
    : Entity(image, X, Y, W, H, l, Qd)
    {
        friendly = Friendly;

        type = frbul;
        range = Range;

        sx = x;
        sy = y;

        ax = 0;
        ay = 0;

        vx = Vx;
        vy = 0;

        sprite.setTextureRect(IntRect(0, 0, w, h));
        if (ax < 0) sprite.setScale(-1, 1);

        b = B;
    }

    void update(double time);
    void boom();

    void drawE (double time, RenderWindow* window);

private:
    bool checkCol(double Vx, double Vy);
};

void Laser::drawE (double time, RenderWindow* window)
{
    window->draw (sprite);
}

void Laser::update(double time)
{
    timer += time;

    for (std::list<Entity*>::iterator b = l->begin(); b != l->end(); b++)
    {
        if (friendly)
        {
            if ((*b)->num != this->num && (*b)->type == unfr &&(*b)->getRekt().intersects(this->getRekt()))
            {
                std::cout << friendly;
                this->boom();

                return;
            }
        }
        else
        {
            if ((*b)->num != this->num && (*b)->type == fr &&(*b)->getRekt().intersects(this->getRekt()))
            {
                this->boom();

                return;
            }
        }
    }

    x += vx * time;
    if (checkCol(vx, 0) == 1) return;

    y += vy * time;
    if (checkCol(0, vy) == 1) return;

    vy += ay * time;

    //sprite.rotate(1 * time);

    sprite.setPosition((float)(x + w / 2), (float)(y + h / 2));

    if (vx >= 1)vx = 1;
}

void Laser::boom()
{
    Explosion *E;

    E = new  Explosion(b, x, y, 32, 28, 1000, 5, friendly, l, Qd);

    l->push_back(E);

    this->del();
}

bool Laser::checkCol(double Vx, double Vy)
{
    for (int i = (int)(y / 32); i < (y + h) / 32; i++)
        for (int j = (int)(x / 32); j < (x + w) / 32; j++)
        {
           if (TileMap[i][j] == '0' || TileMap[i][j] == 'f')
           {
                this->boom();

                return 1;
           }
        }

    return 0;
}

class Lasergun :
    public Weapon
{
    public:
    bool processing;

    Image i, b;

	double vB = 0.4;

    Lasergun (int Ammo, bool Friendly, std::list <Entity*> *l, std::vector < std::list<Entity*>::iterator > *Qd,
			  Entity* Owner)
    : Weapon (Ammo, Friendly, l, Qd, Owner)
    {
        i.loadFromFile("images/lll.png");
        b.loadFromFile("images/boom.png");

        processing = 0;

        magazine = 1;

        reload = 1;
    }

    void update(double time)
    {
        timer += time;

        if (load == 0 && timer >= 1000) load = 1;
    }

    void shoot(int dir, double *x, double *y)
    {
        if (load && processing == 0)
        {
            processing = 1;

            Laser *r;

            r = new Laser (&i, *x, *y, 38, 5, vB * dir, 0.001, 5, &b, friendly, l, Qd);

            l->push_back (r);

            load = 0;
            timer = 0;

            processing = 0;
        }
    }
};

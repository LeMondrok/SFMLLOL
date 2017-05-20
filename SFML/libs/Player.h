#pragma once
#include "libs/Entity.h"
#include "libs/inventory.h"
#include <malloc.h>

class Player :
    public Entity
{
public:
    enum { stay, up, right, down, left, jump} state, dir;
    bool spawn;

    Image bg;

    std::list <Weapon*> weapons;

    Player(Image *image, double X, double Y, int W, int H, std::list <Entity*> *l, std::vector < std::list<Entity*>::iterator > *Qd)
    : Entity(image, X, Y, W, H, l, Qd)
    {
        type = fr;

        sprite.setTextureRect(IntRect(0, 0, w, h));

        state = stay;

        spawn = 1;

        PodushkaMet *b;

        b = new PodushkaMet (8, 1, l, Qd, this);

        weapons.push_back (b);
    }

    void update(double time);

    void drawE (double time, RenderWindow* window);

private:
    void checkCol(double Vx, double Vy);

    void control ();
};

void Player::drawE (double time, RenderWindow* window)
{
    window->draw (sprite);
}

void Player::checkCol(double Vx, double Vy)
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
}

void Player::update(double time)
{
    control();

    switch (state)
    {
        case right : vx =  speed; break;
        case left  : vx = -speed;  break;
        case up    :              break;
        case down  : vx = 0;      break;
        case stay  :              break;
    }

    if (vx > 0) dir = right;
    if (vx < 0) dir = left;

    x += vx * time * 1.2;
    checkCol(vx * 1.2, 0);

    y += vy * time * 1.2;
    checkCol(0, vy * 1.2);

    vy +=  0.0015 * time;

    speed = 0;

    sprite.setPosition((float)(x + w / 2), (float)(y + h / 2));

    setPlayerCoordinateForView(x, y);

    for (std::list<Weapon*>::iterator g = weapons.begin(); g != weapons.end(); g++)
        (*g)->update(time);
}

void Player::control() 
{
    if (sf::Keyboard::isKeyPressed(Keyboard::Left))
    {
        state = left;
        speed = 0.1;
    }
    if (sf::Keyboard::isKeyPressed(Keyboard::Right))
    {
        state = right;
        speed = 0.1;
    }
    if (sf::Keyboard::isKeyPressed(Keyboard::Up) && onGround)
    {
        state = jump;

        onGround = 0;

        vy = -0.6;
    }
    if (sf::Keyboard::isKeyPressed(Keyboard::Down))
    {
        state = down;

        speed = 0;
    }
    if (sf::Keyboard::isKeyPressed(Keyboard::Space))// && spawn == 1)
    {
        if (dir == right)
            (weapons.back())->shoot(1,  &x, &y);
        else
            (weapons.back())->shoot(-1, &x, &y);
    }
}

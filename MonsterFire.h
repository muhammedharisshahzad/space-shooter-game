#ifndef MONSTERFIRE_H
#define MONSTERFIRE_H

#include <iostream>
#include <sfml/Graphics.hpp>

using namespace std;
using namespace sf;

class MonsterFire
{
    private:
        Texture fire_t;
    public:
        Sprite fire_spr;
        MonsterFire()
        {
            fire_t.loadFromFile("images/monster_fire.png");
            fire_spr.setTexture(fire_t);
        }
        void move()
        {
            fire_spr.move(0, 2);
        }
};
#endif
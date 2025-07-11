#ifndef INVADER_H
#define INVADER_H

#include <SFML/Graphics.hpp>
#include "enemies.h"
using namespace sf;
using namespace std;

// alpha invader
class Invader: public Enemies
{
    public:
        Sprite invader;
        Invader(string, int, int);
        void move();
        void operator ^ (float);
};

//functions
Invader::Invader(string path, int x, int y)
{
    inv_tex.loadFromFile(path);
    invader.setTexture(inv_tex);
    invader.setPosition(x, y);
    invader.setScale(0.5, 0.5);
}

void Invader::move()
{
    invader.move(speed, 0);
}

// operator overloading
// to increase speed
void Invader::operator^(float s)
{
    speed = s;
}
#endif
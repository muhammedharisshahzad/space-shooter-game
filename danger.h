#ifndef DANGER_H
#define DANGER_H

#include <SFML/Graphics.hpp>
#include "AddOns.h"
using namespace sf;
using namespace std;

class Danger: public AddOns
{
    public:
        Danger()
        {
            texture.loadFromFile("images/danger.png");
            addOn_spr.setTexture(texture);
        }
};
#endif
#ifndef HEALTH_H
#define HEALTH_H

#include <SFML/Graphics.hpp>
#include "AddOns.h"
using namespace sf;
using namespace std;

class Health: public AddOns
{
    public:
        Health()
        {
            texture.loadFromFile("images/health.png");
            addOn_spr.setTexture(texture);
        }
};
#endif
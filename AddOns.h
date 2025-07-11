#ifndef ADDONS_H
#define ADDONS_H

#include <iostream>
#include <sfml/Graphics.hpp>
#include <time.h>

using namespace std;
using namespace sf;

class AddOns
{
    protected:
        Texture texture;
    public:
        Sprite addOn_spr;
        void setPosition()
        {
            srand(time(0));
            addOn_spr.setPosition(((rand() % (100 - 700 + 1)) + 100), ((rand() % (600 - 300 + 1)) + 300));
        }
        void show_onScreen(RenderWindow* window)
        {
            window->draw(addOn_spr);
        }
        virtual ~AddOns() = default;
};
#endif
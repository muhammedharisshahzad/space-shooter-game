#ifndef MONSTER_H
#define MONSTER_H

#include <sfml/Graphics.hpp>
#include <iostream>
#include "Enemies.h"
#include "MonsterFire.h"
#include <vector>

using namespace std;
using namespace sf;

class Monster: public Enemies
{
    private:
        vector <MonsterFire> fire;
    public:
        Sprite monster_spr;
        Monster()
        {
            inv_tex.loadFromFile("images/monster.png");
            monster_spr.setTexture(inv_tex);
            monster_spr.setPosition(200, 150);
            monster_spr.setScale(0.2, 0.2);
        }
        void move()
        {
            speed = 0.05;
            monster_spr.move(speed, 0);
        }
        void draw(RenderWindow* win)
        {
            win->draw(monster_spr);
        }
        void shoot_fire(RenderWindow* window, Sprite& player, int& lives)
        {
            MonsterFire newfire;
            newfire.fire_spr.setPosition(monster_spr.getPosition());

            fire.push_back(newfire);

            for(int i=0; i<fire.size(); i++)
            {
                window->draw(fire[i].fire_spr);
                fire[i].move();
                
                // if fire collide with player
                if(player.getGlobalBounds().intersects(fire[i].fire_spr.getGlobalBounds()))
                {
                    player.setPosition(340, 700);
                    if(lives == 0)
                    {
                        return;
                    }
                    lives--; 
                }
            }

            // if monster collode with player
            if(monster_spr.getGlobalBounds().intersects(player.getGlobalBounds()))
            {
                player.setPosition(340, 700);
                lives--;
            }
        }
};

#endif
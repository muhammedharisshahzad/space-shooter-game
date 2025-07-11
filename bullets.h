#ifndef BULLETS_H
#define BULLETS_H
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Bullets
{
    private:
        Texture bul_text;
    public:
        Sprite bullet_spr;
        Bullets()
        {
            bul_text.loadFromFile("images/Player_bullet.png");
            bullet_spr.setTexture(bul_text);
            bullet_spr.setScale(0.5, 0.5);
        }
        void shoot(int i, int j)
        {
            bullet_spr.move(i, j);
        }
        void set_position(Vector2f pos)
        {
            bullet_spr.setPosition(pos);
        }
        void drawBul(RenderWindow* win)
        {
            win->draw(bullet_spr);
        }
};
#endif
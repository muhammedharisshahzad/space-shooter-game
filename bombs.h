#ifndef BOMBS_H
#define BOMBS_H
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Bombs
{
    private:
        Texture bomb_text;
    public:
        Sprite bomb_spr;
        Bombs();
        void shoot(float, float);
        void set_position(Vector2f);
        void drawBomb(RenderWindow*);
};
// functions
Bombs::Bombs()
{
    bomb_text.loadFromFile("images/en_bomb.png");
    bomb_spr.setTexture(bomb_text);
    bomb_spr.setScale(0.3 , 0.3);
}
void Bombs::shoot(float i, float j)
{
    bomb_spr.move(i, j);
}
void Bombs::set_position(Vector2f pos)
{
    bomb_spr.setPosition(pos);
}
void Bombs::drawBomb(RenderWindow* win)
{
    win->draw(bomb_spr);
}
#endif
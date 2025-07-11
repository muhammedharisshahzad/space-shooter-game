#ifndef GAMEWON_H
#define GAMEWON_H

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class GameWon
{
    private:
        Texture g_w_t;
        Sprite g_w_sp;
        RenderWindow* window;
    public:
        GameWon()
        {
            g_w_t.loadFromFile("images/GameWon.jpg");
            g_w_sp.setTexture(g_w_t);
            window = new RenderWindow;
        }
        //draw on screen
        void draw_game_won(RenderWindow* win)
        {
            window = win;

            while (window->isOpen())
            {
                Event ev;
                while(window->pollEvent(ev))
                {
                    if (ev.type == Event::Closed)
                        window->close();  
                    if (ev.type == Event::KeyPressed)
                    {
                        if(ev.key.code == Keyboard::Escape)
                            window->close();
                    } 
                }

                window->clear();
                window->draw(g_w_sp);
                window->display();
            }
        }
        // destructor
        ~GameWon()
        {
            delete window;
            window = NULL;
        }
};
#endif
#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SFML/Graphics.hpp>
#include "FileHandling.h"
using namespace sf;
using namespace std;

class GameOver
{
    private:
        Texture g_over;
        Sprite game_over;
        RenderWindow* window;
        FileHandling* files;
    public:
        GameOver()
        {
            g_over.loadFromFile("images/GameOver.jpg");
            game_over.setTexture(g_over);
            files = new FileHandling;
        }
        ~GameOver()
        {
            delete window;
            window = NULL;
            delete files;
            files = NULL;
        }


        void show_gameOver(RenderWindow* win)
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
                window->draw(game_over);
                window->display();
            }
        }

        // if score > high score
        // update file
        void check_highscore(int score)
        {
            if (files->read_score() < score)
            {
                files->update_score(score);
            }
        }
};

#endif
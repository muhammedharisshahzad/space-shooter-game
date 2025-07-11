#ifndef CONTROLS_H
#define CONTROLS_H

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class Controls
{
    private:
        RenderWindow* window;
        Texture bg_text;
        Sprite bg_sprite;
    public:
        //constructor
        Controls()
        {
            bg_text.loadFromFile("images/Controls.jpg");
            bg_sprite.setTexture(bg_text);
        }
        void show_ins(RenderWindow* win)
        {
            window = win;

            while(window->isOpen())
            {
                Event e;
                while (window->pollEvent(e))
                {
                    if (e.type == Event::Closed) // If cross/close is clicked/pressed
                        window->close(); //close the game 
                    //escape button also close game
                    if (e.type == Event::KeyPressed)
                    {
                        if(e.key.code == Keyboard::Escape)
                            window->close();
                    }
                }
                
                // skip controls/go back to menu
                if(Keyboard::isKeyPressed(Keyboard::BackSpace))
                {
                    return;
                }

                window->clear();

                window->draw(bg_sprite);

                window->display();
            }
        }
        ~Controls()
        {
            delete window;
            window = NULL;
        }
};
#endif
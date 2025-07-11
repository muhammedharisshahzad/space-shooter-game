#ifndef MENU_H
#define MENU_H

#include "game.h"
#include "FileHandling.h"
#include "Controls.h"

using namespace sf;

class Menu
{
private:
        Game* game;
        FileHandling* file;
        Controls* cont;

        Texture text_menu;
        Sprite background;
        Font font;
        Text HighScore;
        RenderWindow* window;
public:
    Menu()
    {
        window = new RenderWindow
        (VideoMode(780, 780), "231975-232067-BSSE-2A",
        Style::Close | Style::Resize | Style::Titlebar);

        game = new Game;
        file = new FileHandling;
        cont = new Controls;

        text_menu.loadFromFile("images/MenuScreen.jpg");
        background.setTexture(text_menu);

        font.loadFromFile("MyFont.ttf");

        HighScore.setFont(font);
        HighScore.setFillColor(Color::White);
        HighScore.setCharacterSize(50);
        HighScore.setPosition(151, 120);

        HighScore.setString(to_string(file->read_score()));
    }

    void display_menu()
    {
        //music
        Music audio;
        audio.openFromFile("music.ogg");
        audio.setLoop(true);
        audio.play();

        while (window->isOpen())
        {
            Event ev;
            while(window->pollEvent(ev))
            {
                if (ev.type == Event::Closed) // If cross/close is clicked/pressed
                        window->close(); //close the game 
                    //escape button also close game
                if (ev.type == Event::KeyPressed)
                {
                    if(ev.key.code == Keyboard::Escape)
                            window->close();
                }
            }
            
            if(audio.getStatus()==Music::Stopped)
            {
                audio.play();
            }

            //continue to game by braeking loop
            if(Keyboard::isKeyPressed(Keyboard::Enter))
            {
                break;
            }

            //-------------------------------------//
            //controls screen
            if(Keyboard::isKeyPressed(Keyboard::I))
            {
                cont->show_ins(window);
            }
            //-----------------------------------------//
            
            window->clear();
            window->draw(background);
            window->draw(HighScore);
            window->display();
        }
        
        //calling function
        game->start_game(window);
    }
    ~Menu()
    {
        delete game;
        game = NULL;

        delete window;
        window = NULL;

        delete cont;
        cont = NULL;

        delete file;
        file = NULL;
    }
};
#endif
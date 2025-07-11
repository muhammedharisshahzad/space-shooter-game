#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <vector>

#include "player.h"
#include "invader.h"
#include "GameOver.h"
#include "Bullets.h"
#include "Health.h"
#include "gameWon.h"
#include "bombs.h"
#include "Monster.h"
#include "danger.h"

using namespace sf;
using namespace std;

// functions definitions
class Game
{
    private:
        Sprite background; //Game background sprite
        Texture bg_texture;
        Texture bg_level2;
        Texture bg_level3;
        Player* p;  
        Health* helth;
        GameWon* g_won;
        GameOver* g_over;
        Danger* danger;

        //invaders
        Invader* en_i;
        Invader* en_ii;
        Invader* en_iii;
        Invader* en_iv;
        Invader* en_v;

        // monster
        Monster* monster;

        int score;
        int level;
        int lives;

        Text show_score;
        Text live_show;
        Text show_level;

        Font font;

        RenderWindow* window;

        // vectors
        vector<Bullets> bulletvec; // for player

        //for all 5 enemies
        vector<Bombs> enemy_bombs1;
        vector<Bombs> enemy_bombs2;
        vector<Bombs> enemy_bombs3;
        vector<Bombs> enemy_bombs4;
        vector<Bombs> enemy_bombs5;

    public:
        Game();
        ~Game();
        void PlayerMovement();
        void check_collision_bomb_player();
        void draw_alpha_bombs();
        void realTime_board();
        void enemyMovement();
        void health_grabbed();
        void enemy_damage_and_score_increment();
        void collision_invaders_player();
        void gameOver();
        void invader_bomb_put_in_vector(float&, bool&);
        void Level_Increment();
        void show_Danger_AddOn_on_screen(float&, bool&);
        void show_Health_AddOn_on_screen(float&, bool&);
        void window_clear_render_display(float&, bool&, float&, bool&, float&, bool&);
        void Player_Color();
        void enemy_new_wave();
        void showMonster(float&, bool&);
        void dangerGrabbed();
        void environment_bound_player();
        void start_game(RenderWindow*);
};

Game::Game() 
{
    score = 0;
    lives = 3;
    level = 1;

    p=new Player("images/player_ship.png");
    g_over = new GameOver;
    helth = new Health;
    g_won = new GameWon;
    danger = new Danger;

    //background
    bg_texture.loadFromFile("images/L1.jpg");
    bg_level2.loadFromFile("images/L2.jpg");
    bg_level3.loadFromFile("images/L3.jpg");

    background.setTexture(bg_texture);

    //initializing enemies
    en_i = new Invader("images/enemyGreen1.png", 60, 190);
    en_ii = new Invader("images/enemyRed1.png", 130, 190);
    en_iii = new Invader("images/enemyBlue1.png", 200, 190);
    en_iv = new Invader("images/enemyRed2.png", 270, 190);
    en_v = new Invader("images/enemyGreen2.png", 340, 190);

    //monster
    monster = new Monster;

    // set speed for level 1
    // by using operator overloading
    // of class invdaer
    *en_i ^ 0.05;
    *en_ii ^ 0.05;
    *en_iii ^ 0.05;
    *en_iv ^ 0.05;
    *en_v ^ 0.05;

    // font
    font.loadFromFile("MyFont.ttf");

    show_score.setFont(font);
    show_score.setFillColor(Color::White);
    show_score.setPosition(650, 30);
    show_score.setCharacterSize(18);

    live_show.setFont(font);
    live_show.setFillColor(Color::White);
    live_show.setCharacterSize(18);
    live_show.setPosition(650, 55);

    show_level.setFont(font);
    show_level.setFillColor(Color::White);
    show_level.setCharacterSize(18);
    show_level.setPosition(650, 79);
}

void Game::PlayerMovement()
{
    p->sprite.setRotation(0);   // reset rotation

    if (Keyboard::isKeyPressed(Keyboard::Left)) 
        p->move("l");   
    if (Keyboard::isKeyPressed(Keyboard::Right)) 
        p->move("r"); 
    if (Keyboard::isKeyPressed(Keyboard::Up)) 
        p->move("u");    
   if (Keyboard::isKeyPressed(Keyboard::Down)) 
        p->move("d");  
}

void Game::check_collision_bomb_player()
{
    for(int i=0; i<enemy_bombs1.size(); i++) // as all vectors are of samesize, using 1 loop
    {
        if(p->sprite.getGlobalBounds().intersects(enemy_bombs1[i].bomb_spr.getGlobalBounds())
        || p->sprite.getGlobalBounds().intersects(enemy_bombs2[i].bomb_spr.getGlobalBounds())
        || p->sprite.getGlobalBounds().intersects(enemy_bombs3[i].bomb_spr.getGlobalBounds())
        || p->sprite.getGlobalBounds().intersects(enemy_bombs4[i].bomb_spr.getGlobalBounds())
        || p->sprite.getGlobalBounds().intersects(enemy_bombs5[i].bomb_spr.getGlobalBounds()))
        {
            p->sprite.setPosition(340, 700);
            lives--;
        }
    }
}

void Game::realTime_board()
{
    //display score
    show_score.setString("Score: " + to_string(score));
    //display lives
    live_show.setString("Lives: " + to_string(lives));
    //display level
    show_level.setString("Level: " + to_string(level));
}

void Game::draw_alpha_bombs() 
{
    for(int i = 0; i<enemy_bombs1.size(); i++)
    {
        enemy_bombs1[i].drawBomb(window);
        enemy_bombs1[i].shoot(0, 0.2);

        enemy_bombs2[i].drawBomb(window);
        enemy_bombs2[i].shoot(0, 0.2);

        enemy_bombs3[i].drawBomb(window);
        enemy_bombs3[i].shoot(0, 0.2);

        enemy_bombs4[i].drawBomb(window);
        enemy_bombs4[i].shoot(0, 0.2);

        enemy_bombs5[i].drawBomb(window);
        enemy_bombs5[i].shoot(0, 0.2);
    }
}

void Game::enemyMovement()
{
    en_i->move();
    en_ii->move();
    en_iii->move();
    en_iv->move();
    en_v->move();
}

void Game::health_grabbed()
{
    if(p->sprite.getGlobalBounds().intersects(helth->addOn_spr.getGlobalBounds())
    && lives != 3)
    {
        //send health out of screen
        helth->addOn_spr.setPosition(5000, 5000);
        lives++;
    }
}

void Game::enemy_damage_and_score_increment()
{
    for(int i = 0; i<bulletvec.size(); i++)
    {
        if(en_i->invader.getGlobalBounds().intersects(bulletvec[i].bullet_spr.getGlobalBounds()))
        {
            en_i->invader.setPosition(100000, 100000);
            score += 10*level;
        }
        if(en_ii->invader.getGlobalBounds().intersects(bulletvec[i].bullet_spr.getGlobalBounds()))
        {
            en_ii->invader.setPosition(100000, 100000);
            score += 10*level;
        }
        if(en_iii->invader.getGlobalBounds().intersects(bulletvec[i].bullet_spr.getGlobalBounds()))
        {
            en_iii->invader.setPosition(100000, 100000);
            score += 10*level;
        }
        if(en_iv->invader.getGlobalBounds().intersects(bulletvec[i].bullet_spr.getGlobalBounds()))
        {
            en_iv->invader.setPosition(100000, 100000);
            score += 10*level;
        }
        if(en_v->invader.getGlobalBounds().intersects(bulletvec[i].bullet_spr.getGlobalBounds()))
        {
            en_v->invader.setPosition(100000, 100000);
            score += 10 * level;
        }
    }
}

void Game::collision_invaders_player()
{
    if(p->sprite.getGlobalBounds().intersects(en_i->invader.getGlobalBounds())
    || p->sprite.getGlobalBounds().intersects(en_ii->invader.getGlobalBounds())
    || p->sprite.getGlobalBounds().intersects(en_iii->invader.getGlobalBounds())
    || p->sprite.getGlobalBounds().intersects(en_iv->invader.getGlobalBounds())
    || p->sprite.getGlobalBounds().intersects(en_v->invader.getGlobalBounds()))
    {
        p->sprite.setPosition(340, 700);
        lives--;
    }

}

void Game::gameOver()
{
    if(lives == 0)
    {
        g_over->show_gameOver(window);
        g_over->check_highscore(score);
    }
}

void Game::invader_bomb_put_in_vector(float& timer2, bool& isEnemyFiring)
{
    if(timer2 >= 5.0f) // 5 seonds timer (alpha invaders)
    {
        isEnemyFiring = true;
        timer2 = 0.0f;
    }
    if(isEnemyFiring == true)
    {
        Bombs newbomb;

        newbomb.set_position(en_i->invader.getPosition());
        enemy_bombs1.push_back(newbomb);

        newbomb.set_position(en_ii->invader.getPosition());
        enemy_bombs2.push_back(newbomb);

        newbomb.set_position(en_iii->invader.getPosition());
        enemy_bombs3.push_back(newbomb);

        newbomb.set_position(en_iv->invader.getPosition());
        enemy_bombs4.push_back(newbomb);

        newbomb.set_position(en_v->invader.getPosition());
        enemy_bombs5.push_back(newbomb);

        isEnemyFiring = false;
    }
}

void Game::Level_Increment()
{
    if( en_i->invader.getPosition().x > 100000
    && en_ii->invader.getPosition().x > 100000
    && en_iii->invader.getPosition().x > 100000
    && en_iv->invader.getPosition().x > 100000
    && en_v->invader.getPosition().x > 100000) // all 5 enemy are out of screen
    {
        // check for won game
        if(level == 3)
        {
            g_over->check_highscore(score);
            g_won->draw_game_won(window);
        }
        // reset player position
        p->sprite.setPosition(340, 700);

        // re arrange invaders for next level
        en_i->invader.setPosition(60, 190);
        en_ii->invader.setPosition(130, 190);
        en_iii->invader.setPosition(200, 190);
        en_iv->invader.setPosition(270, 190);
        en_v->invader.setPosition(340, 190);

        level++;

        // speed up invaders
        if(level == 2)
        {
            // speed up by using operator overloading
            *en_i ^ 0.1;
            *en_ii ^ 0.1;
            *en_iii ^ 0.1;
            *en_iv ^ 0.1;
            *en_v ^ 0.1;

            // change background
            background.setTexture(bg_level2);
        }
        else if(level == 3)
        {
            // speed up by using operator overloading
            *en_i ^ 0.2;
            *en_ii ^ 0.2;
            *en_iii ^ 0.2;
            *en_iv ^ 0.2;
            *en_v ^ 0.2;

            // change background
            background.setTexture(bg_level3);
        }   
    }
}

void Game::show_Health_AddOn_on_screen(float& timer, bool& displayHealth)
{
    // after every 10 seconds 
    // stays for 3 seconds
    if(timer >= 10.0f)
    {
        displayHealth = true;
        timer = 0.0f;
    }
    if(displayHealth == true)
    {
        helth->show_onScreen(window);
        if (timer >= 3.0f)
        {
            helth->setPosition();
            displayHealth = false;
            timer = 0.0f;
        }
    }
}

void Game::show_Danger_AddOn_on_screen(float& d_timer, bool& displayDanger)
{
    // after every 6 seconds 
    // stays for 2 seconds
    if(d_timer >= 6.0f)
    {
        displayDanger = true;
        d_timer = 0.0f;
    }
    if(displayDanger == true)
    {
        danger->show_onScreen(window);
        if (d_timer >= 2.0f)
        {
            danger->setPosition();
            displayDanger = false;
            d_timer = 0.0f;
        }
    }
}

void Game::Player_Color()
{
    if(lives == 3)
        p->sprite.setColor(Color::Magenta);
    
    else if(lives == 2)
        p->sprite.setColor(Color::Blue);
    else if (lives == 1)
        p->sprite.setColor(Color::Red);
}

void Game::window_clear_render_display(float& timer, bool& displayHealth, float& m_time, bool& m_appear, float& dangerTimer, bool& displayDanger)
{
    //clear window
    window->clear();

    // drawing background
    window->draw(background);  
    draw_alpha_bombs();                   
    window->draw(p->sprite);
    //draw player bullets
    for(int i = 0; i<bulletvec.size(); i++)
    {
        bulletvec[i].drawBul(window);
        bulletvec[i].shoot(0, -3);
    }
    //invaders
    window->draw(en_i->invader);
    window->draw(en_ii->invader);
    window->draw(en_iii->invader);
    window->draw(en_iv->invader);
    window->draw(en_v->invader);

    //monster
    showMonster(m_time, m_appear);

    // level, lives, score
    window->draw(show_score);
    window->draw(live_show);
    window->draw(show_level);
    show_Health_AddOn_on_screen(timer, displayHealth);
    show_Danger_AddOn_on_screen(dangerTimer, displayDanger);
    showMonster(m_time, m_appear);
    //now rendering window
    window->display();
}

void Game::enemy_new_wave()
{
    //to check that if all invaders move out of screen reset them
    if(en_i->invader.getPosition().x >= 1000 && en_i->invader.getPosition().x < 100000
    || en_ii->invader.getPosition().x >= 1000 && en_ii->invader.getPosition().x < 100000
    || en_iii->invader.getPosition().x >= 1000 && en_iii->invader.getPosition().x < 100000
    || en_iv->invader.getPosition().x >= 1000 && en_iv->invader.getPosition().x < 100000
    || en_v->invader.getPosition().x >= 1000 && en_v->invader.getPosition().x < 100000) 
    {
        //now reset them
        en_i->invader.setPosition(60, 190);
        en_ii->invader.setPosition(130, 190);
        en_iii->invader.setPosition(200, 190);
        en_iv->invader.setPosition(270, 190);
        en_v->invader.setPosition(340, 190);
    }
}

void Game::showMonster(float& MonsterTimer, bool& m_appear)
{
    if(MonsterTimer >= 15.0f)
    {
        m_appear = true;
        MonsterTimer = 0.0f;
    }
    if(m_appear == true)
    {
        // move enemies out of screen
        en_i->invader.setPosition(800, 190);
        en_ii->invader.setPosition(800, 190);
        en_iii->invader.setPosition(800, 190);
        en_iv->invader.setPosition(800, 190);
        en_v->invader.setPosition(800, 190);

        monster->draw(window);
        monster->move();
        monster->shoot_fire(window, p->sprite, lives);
        if(MonsterTimer >= 5.0f)
        {
            m_appear = false;
            MonsterTimer = 0.0f;
        }
    }
}

void Game::dangerGrabbed()
{
    if(p->sprite.getGlobalBounds().intersects(danger->addOn_spr.getGlobalBounds()))
    {
        //send dnager out of screen
        danger->addOn_spr.setPosition(5000, 5000);
        lives--;
    }
}

void Game::environment_bound_player()
{
    // if crossed left boundary
    if (p->sprite.getPosition().x < 0)
    {
        p->sprite.setPosition(780, p->sprite.getPosition().y);
    }
    //if crossed right boundary
    else if (p->sprite.getPosition().x > 780)
    {
        p->sprite.setPosition(0, p->sprite.getPosition().y);
    }
    // if crossed upper boundary
    else if (p->sprite.getPosition().y < 0)
    {
        p->sprite.setPosition(p->sprite.getPosition().x , 780);
    }
    // if crossed lower boundary
    else if (p->sprite.getPosition().y > 780)
    {
        p->sprite.setPosition(p->sprite.getPosition().x , 0);
    }
}

void Game::start_game(RenderWindow* menu_window)
{
    Clock clock;
    float timer=0; // for health add on
    float timer2 = 0; // for enemy bombing
    float monsterTimer = 0; // for mosnter
    float danger_timer = 0; // danger add on
            
    // continue menu window
    window = menu_window;
            
    // booleans to be used in game
    bool isPaused = false;
    bool isFiring = false;
    bool displayHealth = false;
    bool isEnemyFiring = false;
    bool monster_appear = false;
    bool displayDanger = false;

    // game loop
    while (window->isOpen())
    {
        if(!isPaused)
        {
            float time = clock.getElapsedTime().asSeconds(); 
            clock.restart();
            timer += time;  
            timer2 += time;
            monsterTimer += time;
            danger_timer += time;

            //Events
            Event e;
            while (window->pollEvent(e))
            {  
                if (e.type == Event::Closed) 
                {
                    window->close();
                    g_over->check_highscore(score);
                }
                //escape button also close game
                if (e.type == Event::KeyPressed)
                {
                    if(e.key.code == Keyboard::Escape)
                    {
                        window->close();
                        g_over->check_highscore(score);
                    }
                    // Pause the game
                    if (e.key.code == Keyboard::P)
                        isPaused = true;
                } 
                // for firing by player
                if (e.type == Event::KeyReleased)
                {
                    if(e.key.code == Keyboard::Space)
                    {
                        isFiring = true;
                    }
                }                      	    
            }
                    
            //space ship firing
            if(isFiring == true)
            {
                Bullets newbullet;
                newbullet.set_position(p->sprite.getPosition());
                bulletvec.push_back(newbullet);
                isFiring = false;
            }

            //mouse position
            // cout << Mouse::getPosition(*window).x << " " << Mouse::getPosition(*window).y << endl;

            enemy_new_wave();
            Player_Color();
            PlayerMovement();
            environment_bound_player();
            realTime_board();
            collision_invaders_player();
            enemy_damage_and_score_increment();
            Level_Increment();
            check_collision_bomb_player(); 
            gameOver();
            health_grabbed();
            dangerGrabbed();
            enemyMovement();
            invader_bomb_put_in_vector(timer2, isEnemyFiring);
            window_clear_render_display(timer, displayHealth, monsterTimer, monster_appear, danger_timer, displayDanger);
                      
        }
        else //i.e game is pause
        {
            Event e;
            while (window->pollEvent(e))
            {  
                if (e.type == Event::KeyPressed)
                {
                    // Resume the game
                    if (e.key.code == Keyboard::R)
                    isPaused = false;
                }                       	    
            }
        }
    }
}

Game::~Game()
{
    delete p;
    p = NULL;
    delete en_i;
    en_i = NULL;
    delete en_ii;
    en_ii = NULL;
    delete en_iii;
    en_iii = NULL;
    delete en_iv;
    en_iv = NULL;
    delete en_v;
    en_v = NULL;
    delete window;
    window = NULL;
    delete g_over;
    g_over = NULL;
    delete helth;
    helth = NULL; 
    delete g_won;
    g_won = NULL;
    delete monster;
    monster = NULL;
}

#endif
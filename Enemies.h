#ifndef ENEMIES_H
#define ENEMIES_H

#include<SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;


// abstract class (have atleat 1 pure virtual function)
class Enemies
{
    protected:
        float speed;
        Texture inv_tex;
    public:
        // pure virtual function
        virtual void move() = 0; 
        // virtual destructor for clean up
        virtual ~Enemies() = default;
};
#endif
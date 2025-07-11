#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include<string.h>
using namespace sf;
using namespace std;

class Player
{
	public:
		Texture tex;
		Sprite sprite;
		float speed=0.4;
		int x,y;

		Player(string);
		void move(string);
};

//functions
Player::Player(string png_path)
{
		tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		x=340;y=700;
		sprite.setPosition(x,y);
		sprite.setScale(0.75,0.75);
}
void Player::move(string s)
{
	float delta_x=0,delta_y=0;

	if(s=="u")
		delta_y=-1;
	else if(s=="d")
		delta_y=1;
	else if(s=="l")
	{
		delta_x=-1;
		delta_y=-1;
		sprite.setRotation(-10);
	}
	else if(s=="r")
	{
		delta_x=1;
		delta_y=-1;
		sprite.setRotation(10);
	}
	delta_x*=speed;
	delta_y*=speed;

	sprite.move(delta_x, delta_y);
}
#endif
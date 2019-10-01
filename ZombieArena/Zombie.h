#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Zombie
{
	//how fast is each zombie type
	const float BLOATER_SPEED = 40;
	const float CHASER_SPEED = 80;
	const float CRAWLER_SPEED = 20;

	//how tough is each zombie type?
	const float BLOATER_HEALTH = 5;
	const float CHASER_HEALTH = 1;
	const float CRAWLER_HEALTH = 3;

	//make each zombie vary its speed slightly
	const int MAX_VARIANCE = 30;
	const int OFFSET = 101 - MAX_VARIANCE;

	//zombeh position
	Vector2f m_Position;

	//a sprite for zombie
	Sprite m_Sprite;

	//how fast can THIS one rawl/run
	float m_Speed;

	//how much health
	float m_Health;

	//is it still alive?
	bool m_Alive;

	//public prototypes go here
public:
	//Handle when bullet hits a zombie
	bool hit();

	//find out if zomibe is "Alive"
	bool isAlive();

	//spaw a new zombie
	void spawn(float startX, float startY, int type, int seed);

	//return a rectangle that is the position in the world
	FloatRect getPosition();

	//get a copy of the sprite
	Sprite getSprite();

	//update the zombie each frame
	void update(float elapseTime, Vector2f playerLocation);

};
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Pickup {
private:
	//start value for hp pickups
	const int HEALTH_START_VALUE = 50;
	const int AMMO_START_VALUE = 12;
	const int  START_WAIT_TIME = 10;
	const int START_SECONDS_TO_LIVE = 5;
	//sprites for pickups
	Sprite m_Sprite;

	// the arena it exists in
	IntRect m_Arena;

	//how much is it worth?
	int m_Value;
	//what type os it?
	//1 = hp, 2 = ammo
	int m_Type;

	//handle spawning and disaperraing
	bool m_Spawned;
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDespawn;
	float m_SecondsToLive;
	float m_SecondsToWait;

public:
	Pickup(int type);

	//prepare a new thing
	void setArena(IntRect arena);
	void spawn();

	//check pos
	FloatRect getPosition();

	//get sprite
	Sprite getSprite();

	//let pickup update itself
	void update(float elapsedTime);
	 //recive unto the the goodness
	int gotIt();

	bool isSpawned();

	void upgrade();
};
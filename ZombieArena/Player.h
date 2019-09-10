#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player {
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;
	//where is the player
	Vector2f m_Position;
	//speed of the sprite
	Sprite m_Sprite;

	//sprite texture
	//!!WATCH!!
	Texture m_Texture;

	//screen resolution
	Vector2f m_Resolution;

	//size of current arena
	IntRect m_Arena;

	//how big is each tile?
	int m_TileSize;

	//current direction plaer is moving
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;

	//current player health
	int m_Health;

	//players max health
	int m_MaxHealth;

	//when was the player last hit
	Time m_LastHit;

	//speed in pixels per second
	float m_Speed;

	//public functions doi
public:
	Player();
	void spawn(IntRect arena, Vector2f resolution, int tileSize);

	//call this at the end of every game
	void resetPlayerStats();

	//Handle the player getting hit by a zombie
	bool hit(Time timeHit);

	//how long ago was the player last hit
	Time getLastHitTime();

	//Where is the player
	FloatRect getPosition();

	//where is the center of the player
	Vector2f getCenter();

	//which angle is hte player facing
	float getRotation();

	//send a copy of the sprite to the main
	Sprite getSprite();

	//Player movement
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	//stops player from moving in specific direction
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();

	//call this every frame
	void update(float elapsedTime, Vector2i mousePosition);

	//give the player a speed boost
	void upgradeSpeed();

	//give player healths
	void upgradeHealth();

	//increase amount of max health
	void increaseHealthLevel(int amount);

	//get players current health
	void getHealth();

};

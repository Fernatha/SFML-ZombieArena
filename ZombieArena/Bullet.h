#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet {
private:
	//where is the bulleit
	Vector2f m_Position;

	//what each bullet looks like
	RectangleShape m_BulletShape;

	//is the bullet currently doing the thang
	bool m_InFlight = false;

	//how fast des the bullet travel
	float m_BulletSpeed = 1000;

	//what fraction of 1 pixel does the bullet travel
	//horizontally and vertically each frame
	//These values will be derived from m_BulletSpeed
	float m_BulletDistanceX;
	float m_BulletDistanceY;
	//some bounds so the bullet does not fly forever
	float m_MaxX;
	float m_MinX;
	float m_MaxY;
	float m_MinY;

	//public goes here
public:
	//the contructinator
	Bullet();

	//bullet stopinator
	void stop();

	//return value of inFlight
	bool isInFlight();

	//launch a new bulletinator
	void shoot(float startX, float startY,
		float xTaget, float yTarget);

	//get posistion
	FloatRect getPosition();
	//tell the calling code where the bullet is in the world
	RectangleShape getShape();

	//update the bullet each fram
	void update(float elapsedTime);
};

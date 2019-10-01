#include "pch.h"
#include "Zombie.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>

using namespace std;

void Zombie::spawn(float startX, float startY, int type, int seed)
{
	switch (type)
	{
	case 0:
		//Bloater
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/bloater.png"));

		m_Speed = 40;
		m_Health = 5;
		break;

	case 1:
		//Chaser
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/chaser.png"));

		m_Speed = 70;
		m_Health = 1;
		break;

	case 2:
		//crawler
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/crawler.png"));

		m_Speed = 20;
		m_Health = 3;
		break;
	}

	//modify the speed to make zombie unique;
	//every zombie is unique(spercial). create a speed modifier
	srand((int)time(0) * seed);
	//somewhere between 80 and 100
	float modifier = (rand() % MAX_VARIANCE) + OFFSET;

	//express as a fraction
	modifier /= 100; //now equals between .7 and 1
	m_Speed *= modifier;
	//init the location
	m_Position.x = startX;
	m_Position.y = startY;

	//set the origin to its center
	m_Sprite.setOrigin(25, 25);

	//set the position
	m_Sprite.setPosition(m_Position);
}

bool Zombie::hit()
{
	m_Health--;
	if (m_Health < 0);
	{
		//ded
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::GetTexture(
			"graphics/blood.png"));

		return true;
	}
	//injured but not ded
	return false;
}

bool Zombie::isAlive()
{
	return m_Alive;
}

FloatRect Zombie::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite Zombie::getSprite()
{
	return m_Sprite;
}

void Zombie::update(float elapsedTime, Vector2f playerLocation)
{
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	//update the zombie position
	if (playerX > m_Position.x)
	{
		m_Position.x = m_Position.x +
		m_Speed * elapsedTime;
	}
	if (playerY > m_Position.y)
	{
		m_Position.y = m_Position.y +
		m_Speed * elapsedTime;
	}
	if (playerX < m_Position.x)
	{
		m_Position.x = m_Position.x -
			m_Speed * elapsedTime;
	}
	if (playerY < m_Position.y)
	{
		m_Position.y = m_Position.y -
			m_Speed * elapsedTime;
	}

	//move the sprite
	m_Sprite.setPosition(m_Position);

	//face sprite in the right direction

	float angle = (atan2(playerY - m_Position.y,
		playerX - m_Position.x)
		* 180 / 3.141);

	m_Sprite.setRotation(angle);
}
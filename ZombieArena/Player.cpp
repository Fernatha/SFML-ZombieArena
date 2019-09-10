#include "pch.h"
#include "player.h"

Player::Player()
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;

	//associae texture with sprite
	m_Texture.loadFromFile("graphic.player.png");
	m_Sprite.setTexture(m_Texture);

	//set the origin of the sprite to the center
	//for smooth rotation
	m_Sprite.setOrigin(25, 25);
}
void Player::spawn(IntRect arena, Vector2f resolution, int tileSize)
{
	//set player location to middle of arena
	m_position.x = arena.width / 2;
	m_position.y = arena.height / 2;

	//copy the details of the arena to the players m_Arena
	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;

	//remember how big the tiles in the arena are
	m_TileSize = tileSize;

	//store the resoolution for future use
	m_Resolution.x - resolution.x;
	m_Resolution.y- resolution.y;
}
void Player::resetPlayerStats()
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
}
Time Player::getLastHitTime()
{
	return m_LastHit;
}
bool Player::hit(Time timeHit)
{
	if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200) 
	{
		m_LastHit = timeHit;
		m_Health -= 10;
		return true;
	}
	else return false;
}
FloatRect Player::getPosition()
{
	return m_Sprite.getGlobalBounds();
}
Vector2f Player::getCenter()
{
	return m_Position;
}
float Player::getRotation()
{
	return m_Sprite.getRotation();
}
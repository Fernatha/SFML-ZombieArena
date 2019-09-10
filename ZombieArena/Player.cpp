#include "pch.h"
#include "player.h"

Player::Player()
{
	m_speed = START_SPEED;
	m_health = START_HEALTH;
	m_maxHealth = START_HEALTH;

	//Associate a texture with the sprite
	m_texture.loadFromFile("graphics/player.png");
	m_sprite.setTexture(m_texture);

	//set the origin of the sprite to the centre
	//for smoooooooooooooooooth rotation
	m_sprite.setOrigin(25, 25);
}

void Player::spawn(IntRect arena, Vector2f res, int tileSize)
{
	//place plaer in middle
	m_position.x = arena.width / 2;
	m_position.y = arena.height / 2;

	//copy details of arena to the players m_arena
	m_arena.left = arena.left;
	m_arena.width = arena.width;
	m_arena.top = arena.top;
	m_arena.height = arena.height;

	//remember how big the tilesize in this arena is
	m_tileSize = tileSize;

	//store the resolution for future use
	m_resolution.x = res.x;
	m_resolution.y = res.y;

}
void Player::resetPlayerStats()
{
	m_speed = START_SPEED;
	m_health = START_HEALTH;
	m_maxHealth = START_HEALTH;
}

Time Player::getLastHitTime()
{
	return m_lastHit;
}

bool Player::hit(Time timeHit)
{
	if (timeHit.asMilliseconds() - m_lastHit.asMilliseconds() > 200)
	{
		m_lastHit = timeHit;
		m_health -= 10;
		return true;
	}
	else 
	{
		return false;
	}
}

FloatRect Player::getPosition()
{
	return m_sprite.getGlobalBounds();
}

Vector2f Player::getCentre()
{
	return m_position;
}

float Player::getRotation()
{
	return m_sprite.getRotation();
}

Sprite Player::getSprite()
{
	return m_sprite;
}

int Player::getHealth() 
{
	return m_health;
}

void Player::moveLeft()
{
	m_leftPressed = true;
}

void Player::moveRight()
{
	m_rightPressed = true;
}

void Player::moveUp()
{
	m_upPressed = true;
}

void Player::moveDown()
{
	m_downPressed = true;
}

void Player::stopLeft()
{
	m_leftPressed = false;
}

void Player::stopRight()
{
	m_rightPressed = false;
}

void Player::stopUp()
{
	m_upPressed = false;
}

void Player::stopDown()
{
	m_downPressed = false;
}

void Player::update(float elapsedTime, Vector2i mousePosition) 
{
	if (m_upPressed)
	{
		m_position.y -= m_speed * elapsedTime;
	}
	if (m_downPressed)
	{
		m_position.y += m_speed * elapsedTime;
	}
	if (m_leftPressed)
	{
		m_position.x -= m_speed * elapsedTime;
	}
	if (m_rightPressed)
	{
		m_position.x += m_speed * elapsedTime;
	}
	m_sprite.setPosition(m_position);


	//keep the player in the arena
	if (m_position.x > m_arena.width - m_tileSize)
	{
		m_position.x = m_arena.width - m_tileSize;
	}
	if (m_position.x < m_arena.left + m_tileSize)
	{
		m_position.x = m_arena.left + m_tileSize;
	}
	if (m_position.y > m_arena.height - m_tileSize)
	{
		m_position.y = m_arena.height - m_tileSize;
	}
	if (m_position.y < m_arena.height + m_tileSize)
	{
		m_position.y = m_arena.height + m_tileSize;
	}

	//calculate the angle the player is facing
	float angle = (atan2(mousePosition.y - m_resolution.y / 2,
		mousePosition.x - m_resolution.x / 2)
		* 180) / 3.141;

	m_sprite.setRotation(angle);
}

void Player::upgradeSpeed()
{
	//20% speed upgrade
	m_speed += (START_SPEED * .2);
}

void Player::upgradeHealth()
{
	//20% hp upgrade
	m_maxHealth += (START_HEALTH *.2);
}

void Player::increasedHealthLevel(int amount)
{
	m_health += amount;
	//but not beyond the max
	if (m_health > m_maxHealth)
	{
		m_health = m_maxHealth;
	}
}
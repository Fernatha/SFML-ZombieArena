#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player {
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;
	//where is the player
	Vector2f m_position;
	//speed of the sprite
	Sprite m_Sprite;

	//sprite texture
	//!!WATCH!!
	Texture m_Texture;

	//screen resolution
	Vector2f m_Resolution;

};

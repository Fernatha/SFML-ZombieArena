// HelloSfml.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ZombieArena.h"
#include "TextureHolder.h"
#include "Bullet.h"

int main()
{
	//here is the instance of textureholder
	TextureHolder holder;

   // the game will always be in one of four states
	enum class State
	{
		PAUSED, LEVELING_UP, GAME_OVER, PLAYING
	};
	//start with GAME_OVER STATE
	State state = State::GAME_OVER;

	//get the screen res and create an SFML window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y),
		"Zombie Arena", Style::Fullscreen);

	//create an SFML view for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
	//clock for timing
	Clock clock;

	//how long has the PLAYING state been active
	Time gameTimeTotal;
	//where is the mouse in relation to the world coords
	Vector2f mouseWorldPosition;

	//where is the mouse is relation to the screen coords
	Vector2i mouseScreenPosition;

	//create an instance of the player class
	Player player;

	//the boundaries of the arena
	IntRect arena;

	//Create the backgroundvertexArray background
	//load the texture for our background vertex array
	VertexArray background;
	Texture textureBackground = TextureHolder::GetTexture("graphics/background_sheet.png");

	//prepare for a horde of zombies
	int numZombies;
	int numZombiesAlive;
	Zombie* zombies = nullptr;

	//100 bullets oughta deden those deded...?
	Bullet bullets[100];
	int currentBullet = 0;
	int bulletsSpare = 24;
	int bulletsInClip = 6;
	int clipSize = 6;
	float fireRate = 1;
	//when was fire button pressed last
	Time lastPressed;

	// hide the mouse pointer and replace it with a crosshair
	window.setMouseCursorVisible(true);
	Sprite spriteCrossHair;
	Texture textureCrosshair =
		TextureHolder::GetTexture("graphics/crosshair.png");

	spriteCrossHair.setTexture(textureCrosshair);
	spriteCrossHair.setOrigin(25, 25);

	//the main game loop
	while (window.isOpen()) {
		/*
		**************************************
		HANDLE INPUT
		**************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				//pause a game while playing
				if (event.key.code == Keyboard::Return &&
					state == State::PLAYING)
				{
					state = State::PAUSED;
				}
				//restart while paused
				if (event.key.code == Keyboard::Return &&
					state == State::PAUSED)
				{
					state = State::PLAYING;
					//reset the clock so there isnt a frame jump
					clock.restart();
				}
				//start a new game while inGAME_OVER stat
				else if (event.key.code == Keyboard::Return &&
					state == State::GAME_OVER)
				{
					state = State::LEVELING_UP;
				}
				if (state == State::PLAYING)
				{
					//Reloading
					if (event.key.code == Keyboard::R)
					{
						if (bulletsSpare >= clipSize)
						{
							//plenty of bullets, reload
							bulletsInClip = clipSize;
							bulletsSpare -= clipSize;
						}
						else if (bulletsSpare)
						{
							//if only a few bullets left
							bulletsInClip = bulletsSpare;
							bulletsSpare = 0;
						}
						else
						{
							//more to come
						}
					}
				}
			}
		}//end event polling

		//Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		//Handle WASD while playing
		if (state == State::PLAYING)
		{
			//Handle the pressing/releasing of WASD
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player.moveUp();
			}
			else
			{
				player.stopUp();
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player.moveDown();
			}
			else
			{
				player.stopDown();
			}
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				player.moveLeft();
			}
			else
			{
				player.stopLeft();
			}
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				player.moveRight();
			}
			else
			{
				player.stopRight();
			}
			//fire a bullet
			if (Mouse::isButtonPressed(sf::Mouse::Left)) 
			{
				if (gameTimeTotal.asMilliseconds()
					- lastPressed.asMilliseconds() 
					> 1000 / fireRate && bulletsInClip > 0)
				{
					//pass the center of the player
					//and the center of the crosshair
					//to the shoot funtion
					bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y,
						mouseWorldPosition.x, mouseWorldPosition.y);
					currentBullet++;
					if (currentBullet > 99)
					{
						currentBullet = 0;
					}
					lastPressed = gameTimeTotal;
					bulletsInClip--;
				}
			}
		}//emd WASD while playing

		//Handle LEVELING_UP state
		if (state == State::LEVELING_UP)
		{
			//handle the player lvling
			if (event.key.code == Keyboard::Num1)
			{
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num2)
			{
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num3)
			{
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num4)
			{
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num5)
			{
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num6)
			{
				state = State::PLAYING;
			}
			if (state == State::PLAYING)
			{
				//prepare the level
				//this will be modified later, REMOVE COMMENT WHEN DONED
				arena.width = 500;
				arena.height = 500;
				arena.left = 0;
				arena.top = 0;


				//pass vertex array by reference
				//to the createBackground function
				int tileSize = createBackground(background, arena);

				//spawn playier in middle of screen
				player.spawn(arena, resolution, tileSize);

				//create a horde of zombies
				numZombies = 10;

				//delete the previously allocated memory 9if it exists)
				delete[] zombies;
				zombies = createHorde(numZombies, arena);
				numZombiesAlive = numZombies;

				//reset the clock so there is a frame jump
				clock.restart();
			}	
		}//End leveling up 

		/*
		**************************************
		HANDLE THE FRAME
		**************************************
		*/
		if (state == State::PLAYING)
		{
			//update the delta time
			Time dt = clock.restart();

			//update the total game time
			gameTimeTotal += dt;

			//make a decimal fraction of 1 from the delta time
			float dtAsSeconds = dt.asSeconds();

			//wher is the mouse pointer?
			mouseScreenPosition = Mouse::getPosition();

			//convert mouse pos to world coords of mainView
			mouseWorldPosition = window.mapPixelToCoords(
				Mouse::getPosition(), mainView);

			//set the crosshair to the mouse world pos
			spriteCrossHair.setPosition(mouseWorldPosition);

			//update the player
			player.update(dtAsSeconds, Mouse::getPosition());

			//mae a note of the players new position
			Vector2f playerPosition(player.getCenter());

			//make view center around player
			mainView.setCenter(player.getCenter());

			//loop through each zombie and update them
			for (int i = 0; i < numZombies; i++)
			{
				if (zombies[i].isAlive())
				{
					zombies[i].update(dt.asSeconds(), playerPosition);
				}
			}

			//update any bullets that are in flight
			for (int i = 0; i < 100; i++)
			{
				if (bullets[i].isInFlight())
				{
					bullets[i].update(dtAsSeconds);
				}
			}
		
		}//end updating loop

		/*
		**************************************
		DRAW THE SCENE
		**************************************
		*/
		if (state == State::PLAYING)
		{
			window.clear();
			//set mainView to be displayed in the window
			//and draw errythaaaaang related to it....gurrrrrrrl
			window.setView(mainView);

			//draw the background
			window.draw(background, &textureBackground);
			//draw the bullets
			for (int i = 0; i < 100; i++)
			{
				if (bullets[i].isInFlight())
				{
					window.draw(bullets[i].getShape());
				}
			}
			//draw the playa
			window.draw(player.getSprite());

			//draw the crosshair
			window.draw(spriteCrossHair);

			//draw the dedbois
			for (int i = 0; i < numZombies; i++)
			{
				window.draw(zombies[i].getSprite());
			}
			
		}
		if (state == State::LEVELING_UP)
		{

		}
		if (state == State::PAUSED)
		{

		}
		if (state == State::GAME_OVER)
		{

		}
		window.display();
	}//end game loop

	//delete the previously allocated memory(if it exists)
	delete[] zombies;
	return 0;
}

// HelloSfml.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ZombieArena.h"

int main()
{
   //the game will always be in one of four states
	enum class State
	{
		PAUSED, LEVELING_UP, GAME_OVER, PLAYING
	};
	//start with the GAME_OVER state
	State state = State::GAME_OVER;

	//get the screen resolution and create an sfmal window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y),
		"Zombie Arena", Style::Fullscreen);

	//create an SFML view for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
	//here is our clock for timing everything
	Clock clock;

	//how long has the PLAYING state been active
	Time gameTimeTotal;
	//where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;

	//Where is the mouse in relation to the screen coordinates
	Vector2i mouseScreenPosition;

	//create an instance of the PLayer class
	Player player;

	//boundaries of the arena
	IntRect arena;

	//create the backgroundVertexArray background
	VertexArray background;
	//load the texture for the background vertex array
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/background_sheet.png");

	//the main game loop
	while (window.isOpen())
	{
		/*
		*************
		HANDLE INPUT
		*************
		*/

		//handle events by polling
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
				//Restart while paused
				else if (event.key.code == Keyboard::Return &&
					state == State::PAUSED)
				{
					state == State::PLAYING;
					//reset the close so there isnt a frame jump
					clock.restart();
				}
				//start a new game while in GAME_OVER state
				else if (event.key.code == Keyboard::Return &&
					state == State::GAME_OVER)
				{
					state = State::LEVELING_UP;
				}
				if (state == State::PLAYING)
				{

				}
			}
		}//end event polling

		//handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		//handle WASD while playing
		if (state == State::PLAYING)
		{
			//handle the pressing and releasing of the WASD keys
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
		}//END WASD while playing
		
		//handle the leveling up State
		if (state == State::LEVELING_UP)
		{
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
				///////////////////////////////////////
				//we will modify the next 2 lines later
				arena.width = 500;
				arena.height = 500;
				arena.left = 0;
				arena.top = 0;
				
				//Pass the vertex array by reference
				//to the createBackground function
				int tileSize = createBackground(background, arena);
				//////////////////////////////////////

				//spawn the plaer in the middle of the arena
				player.spawn(arena, resolution, tileSize);

				//reset the clock
				clock.restart();
			}
		}//end leveling up

		/*
		*******************
		UPDATE THE FRAME
		*******************
		*/
		if (state == State::PLAYING)
		{
			//update the delta time
			Time dt = clock.restart();

			//Update the total game time
			gameTimeTotal += dt;

			//make a decimal fraction of 1 from the dt
			float dtAsSeconds = dt.asSeconds();

			//where is the mouse pointer
			mouseScreenPosition = Mouse::getPosition();

			//convert mouse pos to world coordinates of mainView
			mouseWorldPosition = window.mapPixelToCoords(
				Mouse::getPosition(), mainView);

			//update the player
			player.update(dtAsSeconds, Mouse::getPosition());

			//make note of a players new pos
			Vector2f playerPosition(player.getCentre());

			//Make the view centre around the player
			mainView.setCenter(player.getCentre());
		}//End updating the scene

		/*
		*****************
		Draw the scene
		*****************
		*/
		if (state == State::PLAYING)
		{
			window.clear();
			//set the mainView to bedisplayed in the window
			//and draw everything related to it
			window.setView(mainView);

			//draw the background
			window.draw(background, &textureBackground);

			//draw the player
			window.draw(player.getSprite());
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
	}//end the game loop
	return 0;
}

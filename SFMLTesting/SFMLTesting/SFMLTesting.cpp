// SFMLTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include "Functions.h"

//main function
int main()
{
	//seed the random number generator
	srand(time(NULL));

	//Declare variables
	bool close = false;
	int difficulty = 2;			//Define a number one more than the number of squares
	int score = 0;
	std::vector<sf::RectangleShape> enemies;

	//Character properties
	float characterX = 40;
	float characterY = characterX;

	sf::RectangleShape character(sf::Vector2f(characterX, characterY));
	character.setFillColor(sf::Color(0, 0, 255, 255));

	//enemy properties
	float rectX = 20;
	float rectY = rectX;

	//window properties
	float windowX = 800;
	float windowY = 600;


	// create the window
	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "My window");

	//goal properties
	sf::RectangleShape goalSquare(sf::Vector2f(30, 30));

	goalSquare.setFillColor(sf::Color(0, 255, 0, 255));
	goalSquare.setPosition((windowX - 50), (windowY - 50));

	//Create all the enemies
	enemies = CreateEnemies(enemies, difficulty, rectX, rectY);

	///MAIN MENU
	window.clear(sf::Color::Black);

	//system("pause");

	///GAME LOOP
	while (window.isOpen())
	{
		// check all window events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//call functions
		//character functions
		character = MovingAround(character);
		character = DecidePosition(character, windowX, windowY, characterX);

		//check score
		if (Collision(character, goalSquare)) 
		{
			
			//add to your score
			score += 1;

			//reset the character
			character.setPosition(10, 10);

			//write your score
			std::cout << score << std::endl;

			//increase the difficulty
			difficulty += 1;

			//clear the vector
			enemies.clear();

			//generate new enemies
			enemies = CreateEnemies(enemies, difficulty, rectX, rectY);

		}

		//Determmine collisions
		close = Collision(character, enemies[0]);

		for (int i = 1; i < (difficulty - 1); i++)
		{
			if (close == false)
			{

				close = Collision(character, enemies[i]);

			}
		} 

		//close if collision
		if (close == true) 
		{
		
			//clear the vector
			enemies.clear();

			//create more enemies
			enemies = CreateEnemies(enemies, difficulty, rectX, rectY);

			//reset the character
			character.setPosition(10, 10);

			//reset the score
			score = 0;

			//reset collision detection variable
			close = false;

			difficulty = 2;
		
		}

		//clear the window
		window.clear(sf::Color::Black);

		//drawing
		for (int i = 0; i < (difficulty - 1); i++) 
		{
		
			window.draw(enemies[i]);
		
		}

		window.draw(goalSquare);
		window.draw(character);

		//end the frame
		window.display();

	}

	return 0;
}
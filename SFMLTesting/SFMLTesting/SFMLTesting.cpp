// SFMLTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>

//define classes
sf::RectangleShape MovingAround(sf::RectangleShape shape);
sf::RectangleShape DecidePosition(sf::RectangleShape shape, float windowX, float windowY, float characterX);
sf::RectangleShape RectanglePosition(sf::RectangleShape shape, float windowX, float windowY);
bool Collision(sf::RectangleShape object1, sf::RectangleShape object2);
int RandomNumber(int myMod);

std::vector<sf::RectangleShape> CreateEnemies(std::vector<sf::RectangleShape>& enemies, int difficulty, float rectX, float rectY);

//main function
int main()
{

	//seed the random number generator
	srand(time(NULL));

	//Declare variables
	bool close = false;
	int difficulty = 11;			//Define a number one more than the number of squares
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

	system("pause");

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
		
			score += 1;
			character.setPosition(10, 10);
			std::cout << score << std::endl;
		
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
		
			enemies = CreateEnemies(enemies, difficulty, rectX, rectY);
			character.setPosition(10, 10);
			score = 0;
			close = false;
		
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

//Check to see if the shape is at the edge of the window and then reset position
sf::RectangleShape DecidePosition(sf::RectangleShape shape, float windowX, float windowY, float characterX)
{

	//declare variables
	sf::Vector2f position = shape.getPosition();
	float shapeX = position.x;
	float shapeY = position.y;
	float diameter = characterX;

	//check for being out of bounds
	if (shapeX > windowX - diameter)
	{
	
		shape.setPosition(windowX - diameter, shapeY);
	
	}
	else if (shapeX < 0) 
	{
	
		shape.setPosition(0, shapeY);
	
	}
	
	if (shapeY > windowY - diameter) 
	{
	
		shape.setPosition(shapeX, windowY - diameter);
	
	}
	else if (shapeY < 0) 
	{
	
		shape.setPosition(shapeX, 0);
	
	}

	return shape;
	
}

//Move the character around the screen
sf::RectangleShape MovingAround (sf::RectangleShape shape) 
{

	//declare variables
	float speed = 0.5;

	//Check for input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
	{
	
		//move right
		shape.move(speed, 0);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
	{
	
		//move left
		shape.move(-speed, 0);
	
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
	{

		//move up
		shape.move(0, -speed);
	
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
	{
	
		//move down
		shape.move(0, speed);
	
	}

	return shape;
}

//draw the enemies
sf::RectangleShape RectanglePosition(sf::RectangleShape shape, float windowX, float windowY) 
{

	int myX = RandomNumber(windowX);
	int myY = RandomNumber(windowY);

	shape.setPosition(myX, myY);

	return shape;

}

//check for collisions
bool Collision(sf::RectangleShape object1, sf::RectangleShape object2) 
{

	if (object1.getGlobalBounds().intersects(object2.getGlobalBounds()))
	{

		//if in collision with the second passed object
		return true;

	}
	else
	{
		
		//if not in collision with the second passed object
		return false;

	}
}

//Generate a random number
int RandomNumber(int myMod)
{

		//declare a random number variable
		int randomNumber;

		//get the random number
		randomNumber = rand() % myMod + 1;

		return randomNumber;

}

//initialize the random enemies
std::vector<sf::RectangleShape> CreateEnemies(std::vector<sf::RectangleShape>& enemies, int difficulty, float rectX, float rectY) 
{

	sf::RectangleShape enemy;

	for (int i = 1; i < difficulty; ++i) 
	{
	
		sf::RectangleShape enemy(sf::Vector2f(rectX, rectY));

		enemy.setFillColor(sf::Color(255, 0, 0, 255));

		enemy = RectanglePosition(enemy, 800, 600);

		enemies.push_back(enemy);
	
	}

	return enemies;
}
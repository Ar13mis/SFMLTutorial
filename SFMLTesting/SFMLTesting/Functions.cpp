#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include "Functions.h"

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
sf::RectangleShape MovingAround(sf::RectangleShape shape)
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
	int randomNumber = rand() % myMod;

	if (randomNumber < myMod)
	{



	}

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
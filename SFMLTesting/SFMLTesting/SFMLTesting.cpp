// SFMLTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>

sf::RectangleShape MovingAround(sf::RectangleShape shape, sf::RectangleShape square);
sf::RectangleShape DecidePosition(sf::RectangleShape shape, float windowX, float windowY, float characterX);
sf::RectangleShape RectanglePosition(sf::RectangleShape shape);
bool Collision(sf::RectangleShape object1, sf::RectangleShape object2);

float drawShapeX;
float drawShapeY;

int main()
{

	bool close = false;

	float characterX = 40;
	float characterY = characterX;

	float rectX = 20;
	float rectY = rectX;

	float windowX = 800;
	float windowY = 600;

	sf::RectangleShape character(sf::Vector2f(characterX, characterY));
	sf::RectangleShape square(sf::Vector2f(rectX, rectY));

	character.setFillColor(sf::Color(255, 0, 0, 255));

	// create the window
	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "My window");

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//call functions
		character = MovingAround(character, square);
		character = DecidePosition(character, windowX, windowY, characterX);

		square = RectanglePosition(square);

		close = Collision(character, square);

		if (close == true) 
		{
		
			window.close();
		
		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		window.draw(square);
		window.draw(character);

		// end the current frame
		window.display();
	}

	return 0;
}

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

sf::RectangleShape MovingAround (sf::RectangleShape shape, sf::RectangleShape square) 
{

	float speed = 0.5;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
	{
	
		shape.move(speed, 0);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
	{
	
		shape.move(-speed, 0);
	
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
	{

		shape.move(0, -speed);
	
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
	{
	
		shape.move(0, speed);
	
	}

	return shape;
}

sf::RectangleShape RectanglePosition(sf::RectangleShape shape) 
{

	shape.setPosition(200, 100);

	return shape;

}

bool Collision(sf::RectangleShape object1, sf::RectangleShape object2) 
{

	int counter = 0;

	if (object1.getGlobalBounds().intersects(object2.getGlobalBounds()))
	{

		return true;

	}
	else
	{

		return false;

	}
}
// SFMLTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>

sf::CircleShape MovingAround(sf::CircleShape shape);
sf::CircleShape DecidePosition(sf::CircleShape shape, float windowX, float windowY, float radius);

float drawShapeX;
float drawShapeY;

int main()
{

	float radius = 40;

	float windowX = 800;
	float windowY = 600;

	sf::CircleShape circle(radius);

	circle.setFillColor(sf::Color(255, 255, 255, 255));

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
		circle = MovingAround(circle);
		circle = DecidePosition(circle, windowX, windowY, radius);

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		window.draw(circle);

		// end the current frame
		window.display();
	}

	return 0;
}


sf::CircleShape DecidePosition(sf::CircleShape shape, float windowX, float windowY, float radius) 
{

	//declare variables
	sf::Vector2f position = shape.getPosition();
	float shapeX = position.x;
	float shapeY = position.y;
	float diameter = radius * 2;

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

sf::CircleShape MovingAround (sf::CircleShape shape) 
{

	float speed = 0.5;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
	{
	
		//shapeX += 1;
		shape.move(speed, 0);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
	{
	
		//shapeX -= 1;
		shape.move(-speed, 0);
	
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
	{

		//shapeY -= 1;
		shape.move(0, -speed);
	
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
	{
	
		//shapeY += 1;
		shape.move(0, speed);
	
	}

	return shape;
}
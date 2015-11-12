// SFMLTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>

sf::CircleShape MovingAround(sf::CircleShape shape);
sf::CircleShape DrawLocation(sf::CircleShape shape, float windowX, float windowY);

float shapeX;
float shapeY;

int main()
{

	float radius = 40;

	float windowX = 800;
	float windowY = 600;

	unsigned int windowXInt = windowX;
	unsigned int windowYInt = windowY;

	sf::CircleShape circle(radius);

	circle.setFillColor(sf::Color(255, 255, 255, 255));
	circle.setOutlineThickness(10);
	circle.setOutlineColor(sf::Color(255, 0, 0));

	// create the window
	sf::RenderWindow window(sf::VideoMode(windowXInt, windowYInt), "My window");

	// run the program as long as the window is open
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

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		window.draw(circle);

		// end the current frame
		window.display();
	}

	return 0;
}


sf::CircleShape MovingAround (sf::CircleShape shape) 
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
	{
	
		//shapeX += 1;
		shape.move(1, 0);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
	{
	
		//shapeX -= 1;
		shape.move(-1, 0);
	
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
	{

		//shapeY -= 1;
		shape.move(0, -1);
	
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
	{
	
		//shapeY += 1;
		shape.move(0, 1);
	
	}

	return shape;
}
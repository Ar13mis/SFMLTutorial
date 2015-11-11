// SFMLTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>

sf::CircleShape MovingAround(sf::CircleShape shape);

int main()
{

	sf::CircleShape circle(50);

	circle.setFillColor(sf::Color::Cyan);

	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

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
		circle = MovingAround (circle);

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
	
		shape.move(1, 0);
	
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
	{
	
		shape.move(-1, 0);
	
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
	{
	
		shape.move(0, -1);
	
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
	{
	
		shape.move(0, 1);
	
	}

	return shape;
}
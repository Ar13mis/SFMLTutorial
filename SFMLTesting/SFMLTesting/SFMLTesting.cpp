// SFMLTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>

//define classes
sf::RectangleShape MovingAround(sf::RectangleShape shape, sf::RectangleShape square);
sf::RectangleShape DecidePosition(sf::RectangleShape shape, float windowX, float windowY, float characterX);
sf::RectangleShape RectanglePosition(sf::RectangleShape shape);
bool Collision(sf::RectangleShape object1, sf::RectangleShape object2);

//main function
int main()
{

	//Declare variables
	bool close = false;

	//Character properties
	float characterX = 40;
	float characterY = characterX;

	sf::RectangleShape character(sf::Vector2f(characterX, characterY));
	character.setFillColor(sf::Color(255, 0, 0, 255));

	//enemy properties
	float rectX = 20;
	float rectY = rectX;

	sf::RectangleShape square(sf::Vector2f(rectX, rectY));	

	//window properties
	float windowX = 800;
	float windowY = 600;



	// create the window
	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "My window");

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
		character = MovingAround(character, square);
		character = DecidePosition(character, windowX, windowY, characterX);

		//enemy functions
		square = RectanglePosition(square);

		//test for collision
		close = Collision(character, square);

		//close if collision
		if (close == true) 
		{
		
			window.close();
		
		}

		//clear the window
		window.clear(sf::Color::Black);

		//drawing
		window.draw(square);
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
sf::RectangleShape MovingAround (sf::RectangleShape shape, sf::RectangleShape square) 
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
sf::RectangleShape RectanglePosition(sf::RectangleShape shape) 
{

	shape.setPosition(200, 100);

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
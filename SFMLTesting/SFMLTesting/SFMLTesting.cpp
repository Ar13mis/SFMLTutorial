// SFMLTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

//define classes
sf::RectangleShape* MovingAround(sf::RectangleShape *shape);
sf::RectangleShape* DecidePosition(sf::RectangleShape *shape, float windowX, float windowY, float characterX);
sf::RectangleShape* RectanglePosition(sf::RectangleShape *shape, float windowX, float windowY);
bool Collision(sf::RectangleShape *object1, sf::RectangleShape* object2);
void CreateEnemies(std::vector<sf::RectangleShape*> shapes, int difficulty, int rectX, int rectY, float windowX, float windowY);
bool EnemyCollision(std::vector<sf::RectangleShape*> shapes, sf::RectangleShape* character);
sf::RectangleShape* DrawEnemies(std::vector<sf::RectangleShape*> shapes);
int RandomNumber(int myMod);

//main function
int main()
{

	//declare enemy vector
	std::vector<sf::RectangleShape*> shapes;

	//seed the random number generator
	srand(time(NULL));

	//Declare variables
	bool close = false;
	bool goal = false;
	int difficulty = 6;
	sf::RectangleShape *enemy;

	//Character properties
	float characterX = 40;
	float characterY = characterX;

	sf::RectangleShape *character = new sf::RectangleShape(sf::Vector2f(characterX, characterY));
	character->setFillColor(sf::Color(0, 0, 255, 255));

	//goal properties
	float goalX = 30;
	float goalY = goalX;

	sf::RectangleShape *goalShape = new sf::RectangleShape(sf::Vector2f(goalX, goalY));
	goalShape->setFillColor(sf::Color(0, 255, 0, 255));

	//enemy properties
	float rectX = 20;
	float rectY = rectX;

	//window properties
	float windowX = 800;
	float windowY = 600;

	//create the goal
	goalShape->setPosition((windowX - 100), (windowY - 100));

	//create enemies
	CreateEnemies(shapes, difficulty, rectX, rectY, windowX, windowY);


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
		character = MovingAround(character);
		character = DecidePosition(character, windowX, windowY, characterX);

		goal = Collision(character, goalShape);
		if (goal == true) 
		{
		
			std::cout << "Collision with goal" << std::endl;
		
		}

		//close if collision
		if (close == true) 
		{
		
			window.close();
		
		}

		//clear the window
		window.clear(sf::Color::Black);

		//drawing
		for (int i = 0; i < difficulty; ++i) 
		{
		
			enemy = DrawEnemies(shapes);
			window.draw(*enemy);

		}

		window.draw(*goalShape);
		window.draw(*character);

		//end the frame
		window.display();
	}

	return 0;
}

//Check to see if the shape is at the edge of the window and then reset position
sf::RectangleShape *DecidePosition(sf::RectangleShape* shape, float windowX, float windowY, float characterX)
{

	//declare variables
	sf::Vector2f position = shape->getPosition();
	float shapeX = position.x;
	float shapeY = position.y;
	float diameter = characterX;

	//check for being out of bounds
	if (shapeX > windowX - diameter)
	{
	
		shape->setPosition(windowX - diameter, shapeY);
	
	}
	else if (shapeX < 0) 
	{
	
		shape->setPosition(0, shapeY);
	
	}
	
	if (shapeY > windowY - diameter) 
	{
	
		shape->setPosition(shapeX, windowY - diameter);
	
	}
	else if (shapeY < 0) 
	{
	
		shape->setPosition(shapeX, 0);
	
	}

	return shape;
	
}

//Move the character around the screen
sf::RectangleShape* MovingAround (sf::RectangleShape* shape) 
{

	//declare variables
	float speed = 0.5;

	//Check for input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
	{
	
		//move right
		shape->move(speed, 0);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
	{
	
		//move left
		shape->move(-speed, 0);
	
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
	{

		//move up
		shape->move(0, -speed);
	
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
	{
	
		//move down
		shape->move(0, speed);
	
	}

	return shape;
}

//draw the enemies
sf::RectangleShape* RectanglePosition(sf::RectangleShape* shape, float windowX, float windowY) 
{

	int myX = RandomNumber(windowX);
	int myY = RandomNumber(windowY);

	shape->setPosition(myX, myY);

	return shape;

}

//check for collisions
bool Collision(sf::RectangleShape* object1, sf::RectangleShape* object2) 
{

	if (object1->getGlobalBounds().intersects(object2->getGlobalBounds()))
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

//Create enemies
void CreateEnemies(std::vector<sf::RectangleShape*> shapes, int difficulty, int rectX, int rectY, float windowX, float windowY) 
{
	
	for (int i = 0; i < difficulty; ++i) 
	{

		//declare the shape
		sf::RectangleShape *shape = new sf::RectangleShape(sf::Vector2f(rectX, rectY));

		//define parts of the shape
		shape->setFillColor(sf::Color(255, 0, 0, 255));
		shape = RectanglePosition(shape, windowX, windowY);

		//return the shape to the array
		shapes.push_back(shape);

	}

}

//check the collision of the enemies
bool EnemyCollision(std::vector<sf::RectangleShape*> shapes, sf::RectangleShape* character) 
{

	for (auto it = shapes.begin(); it != shapes.end(); ++it) 
	{

		sf::RectangleShape *shape = *it;

		if (Collision(character, shape)) 
		{

			return true;

		}
		else
		{

			return false;

		}

	}

}

//draw the enemies to the screen
sf::RectangleShape* DrawEnemies(std::vector<sf::RectangleShape*> shapes) 
{

	for (auto it = shapes.begin(); it != shapes.end(); ++it)
	{
		return *it;
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
#pragma once
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

sf::RectangleShape MovingAround(sf::RectangleShape shape);
sf::RectangleShape DecidePosition(sf::RectangleShape shape, float windowX, float windowY, float characterX);
sf::RectangleShape RectanglePosition(sf::RectangleShape shape, float windowX, float windowY);
bool Collision(sf::RectangleShape object1, sf::RectangleShape object2);
int RandomNumber(int myMod);

std::vector<sf::RectangleShape> CreateEnemies(std::vector<sf::RectangleShape>& enemies, int difficulty, float rectX, float rectY);

#endif
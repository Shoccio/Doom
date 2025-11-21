#pragma once
#include <SFML/Graphics.hpp>

class Player
{
	
	sf::Texture texture = sf::Texture("Assets\\sprite.png");
	sf::Sprite sprite = sf::Sprite(texture);
	sf::Angle rotation = sf::degrees(180.f);
	sf::Angle fov = sf::degrees(60.f);
	float speed = 0.2f, rotationSpeed = 0.2f;

	float degreesToRadians(float);
	public:
		Player();
		void Movement();
		sf::Sprite& getSprite() { return sprite; }
		sf::Angle& getFov() { return fov; }
		sf::Angle& getRotation() { return rotation; }

		

};
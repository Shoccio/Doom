#pragma once
#include <SFML/Graphics.hpp>

class Player : public sf::CircleShape
{
	public:
		Player(sf::Texture* texture = nullprt)
		{
			setRadius(50.f);
			setFillColor(sf::Color::Green);
			setPosition(sf::Vector2f(960.f, 540.f));
		}

};
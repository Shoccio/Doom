#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerMovement.h"
#include "math.h"

float acceleration = 2.0f, Xvelocity = 0.f, YVelocity = 0.f, max = 2.f;
sf::Clock deltaClock;

void HandlePlayerMovement(sf::CircleShape& shape)
{
	float time = deltaClock.getElapsedTime().asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		CheckPosVelocity(YVelocity, time);

		shape.move(VectorF(0.f, -YVelocity));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		CheckNegVelocity(YVelocity, time);
		shape.move(VectorF(0.f, -YVelocity));
	}
	else
	{
		YVelocity = 0.f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		CheckPosVelocity(Xvelocity, time);
		shape.move(VectorF(-Xvelocity, 0.f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		CheckNegVelocity(Xvelocity, time);
		shape.move(VectorF(-Xvelocity, 0.f));
	}
	else
	{
		Xvelocity = 0.f;
	}
	deltaClock.restart();
}

void CheckPosVelocity(float& velocity, float time)
{
	if (std::abs(velocity) < max)
		velocity += acceleration * time;
	else
		velocity = max;
}

void CheckNegVelocity(float& velocity, float time)
{
	if(std::abs(velocity) > -max)
		velocity -= acceleration * time;
	else
		velocity = -max;
}

sf::Vector2f VectorF(float x, float y)
{
	return sf::Vector2f(x, y);
}
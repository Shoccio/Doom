#include <SFML/Graphics.hpp>
#include "Player.h"

Player::Player()
{
	sprite.setPosition(sf::Vector2f(960.f, 540.f));
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f - 6.f));
	sprite.setRotation(rotation);
}

void Player::Movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		float xVector = std::cos(degreesToRadians(rotation.asDegrees())) * speed;
		float yVector = std::sin(degreesToRadians(rotation.asDegrees())) * speed;

		sprite.move(sf::Vector2f(xVector, yVector));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		float xVector = std::cos(degreesToRadians(rotation.asDegrees())) * speed;
		float yVector = std::sin(degreesToRadians(rotation.asDegrees())) * speed;
		sprite.move(sf::Vector2f(-xVector, -yVector));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		rotation -= sf::degrees(rotationSpeed);

		if (rotation.asDegrees() < 0.f)
			rotation += sf::degrees(360.f);
		sprite.setRotation(rotation);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		rotation += sf::degrees(rotationSpeed);
		if (rotation.asDegrees() > 360.f)
			rotation -= sf::degrees(360.f);
		sprite.setRotation(rotation);
	}

}

float Player::degreesToRadians(float degrees)
{
	return degrees * 3.14159265359f / 180.f;
}
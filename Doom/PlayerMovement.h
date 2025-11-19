#pragma once
#include <SFML/Graphics.hpp>

void HandlePlayerMovement(sf::CircleShape&);
void CheckPosVelocity(float&, float);
void CheckNegVelocity(float&, float);
sf::Vector2f VectorF(float, float);
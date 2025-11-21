#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <vector>
#include <tuple>

class RayCast
{
	Player& player;
	std::vector<sf::VertexArray> objects;
	int screenHeight;
	int screenWidth;
	sf::VertexArray fan;
	float maxDistance = 500.f;
	int vertexCount = 60;

	sf::Vector2f findIntersectionPoint(sf::Vector2f, sf::Vector2f);

	bool checkIntersection(float[3], float[3], sf::Vector2f&);
	void twoPointToLine(sf::Vector2f, sf::Vector2f, float&, float&, float&);
	public:
		RayCast(Player&, std::vector<sf::VertexArray>, int, int);
		void update();
		void draw(sf::RenderWindow& window) { window.draw(fan); }
};
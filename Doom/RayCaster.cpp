#include "RayCaster.h"
#include <iostream>
#include <limits>

RayCaster::RayCaster(std::vector<sf::VertexArray*>& walls) : walls(walls)
{
    intersections.reserve(rayCount);
    // Initialize the TriangleFan with enough vertices (rayCount + 2: center + ray endpoints + closing vertex)
    rayFan = sf::VertexArray(sf::PrimitiveType::TriangleFan, rayCount + 2);
}

void RayCaster::castRays(Player& player)
{
    intersections.clear();

    sf::Vector2f playerPos = player.getSprite().getPosition();

    // Get player rotation in radians
    float playerAngle = player.getSprite().getRotation().asRadians();

    // Convert FOV from degrees to radians for calculations
    float fovRad = fov * 3.14159265359f / 180.f;

    float startAngle = playerAngle - (fovRad / 2.f);
    float angleStep = fovRad / static_cast<float>(rayCount);

    // Set the center point of the TriangleFan (player position)
    rayFan[0].position = playerPos;
    rayFan[0].color = sf::Color::Blue;

    for (int i = 0; i <= rayCount; i++)
    {
        float currentAngle = startAngle + (angleStep * i);
        float distance = 0.f;

        sf::Vector2f hitPoint = castSingleRay(player, currentAngle, distance);

        // Set vertex position in the TriangleFan
        // +1 because vertex 0 is the center point
        rayFan[i + 1].position = hitPoint;
        rayFan[i + 1].color = sf::Color(0, 0, 255, 100); // Semi-transparent blue

        // Create intersection point (optional - keep if you still want red dots)
        sf::VertexArray intersectionPoint(sf::PrimitiveType::Points, 1);
        intersectionPoint[0].position = hitPoint;
        intersectionPoint[0].color = sf::Color::Red;
        intersections.push_back(intersectionPoint);
    }
}

sf::Vector2f RayCaster::castSingleRay(Player& player, float angle, float& distance)
{
    sf::Vector2f playerPos = player.getSprite().getPosition();

    // Calculate ray direction (angle is already in radians)
    sf::Vector2f rayDir(
        std::cos(angle),
        std::sin(angle)
    );

    // Calculate ray end point
    sf::Vector2f rayEnd = playerPos + rayDir * maxRayDistance;

    sf::Vector2f closestIntersection = rayEnd; // Default to max distance
    float closestDistance = maxRayDistance;

    // Check intersection with all walls
    for (auto wall : walls)
    {
        // Each wall is a LineStrip with multiple points
        for (size_t i = 0; i < wall->getVertexCount() - 1; i++)
        {
            sf::Vector2f wallStart = (*wall)[i].position;
            sf::Vector2f wallEnd = (*wall)[i + 1].position;

            sf::Vector2f intersection;
            if (lineIntersection(playerPos, rayEnd, wallStart, wallEnd, intersection))
            {
                float dist = std::sqrt(
                    std::pow(intersection.x - playerPos.x, 2) +
                    std::pow(intersection.y - playerPos.y, 2)
                );

                if (dist < closestDistance)
                {
                    closestDistance = dist;
                    closestIntersection = intersection;
                }
            }
        }
    }

    distance = closestDistance;
    return closestIntersection;
}

bool RayCaster::lineIntersection(const sf::Vector2f& rayStart, const sf::Vector2f& rayEnd,
    const sf::Vector2f& wallStart, const sf::Vector2f& wallEnd,
    sf::Vector2f& intersection)
{
    float x1 = rayStart.x, y1 = rayStart.y;
    float x2 = rayEnd.x, y2 = rayEnd.y;
    float x3 = wallStart.x, y3 = wallStart.y;
    float x4 = wallEnd.x, y4 = wallEnd.y;

    float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    if (den == 0) return false; // Lines are parallel

    float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
    float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

    if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
    {
        intersection.x = x1 + t * (x2 - x1);
        intersection.y = y1 + t * (y2 - y1);
        return true;
    }

    return false;
}

void RayCaster::draw(sf::RenderWindow& window)
{
    // Draw the TriangleFan (blue field of view)
    window.draw(rayFan);

    // Draw intersection points (optional - remove if you don't want red dots)
    for (auto& intersection : intersections)
    {
        window.draw(intersection);
    }
}
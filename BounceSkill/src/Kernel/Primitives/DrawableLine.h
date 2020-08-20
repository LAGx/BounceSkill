#pragma once
#include "../IDrawable.h"
#include "SFML/Graphics/ConvexShape.hpp"
#include "glm/vec2.hpp"

class DrawableLine : IDrawable {
public:
	DrawableLine() = delete;
	DrawableLine(glm::vec2 pointA, glm::vec2 pointB, float width, sf::Color color);

	// IDrawable
	void render(sf::RenderWindow&) override;

private:
	void setupLine(glm::vec2 pointA, glm::vec2 pointB, float width);

private:
	sf::ConvexShape freeConvex;
};
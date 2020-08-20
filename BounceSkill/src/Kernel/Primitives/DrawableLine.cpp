#include "DrawableLine.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Math.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using vec2 = glm::vec2;

DrawableLine::DrawableLine(glm::vec2 pointA, glm::vec2 pointB, float width, sf::Color color)
	: freeConvex(4) {
	freeConvex.setFillColor(color);
	setupLine(pointA, pointB, width);
}

// IDrawable
void DrawableLine::render(sf::RenderWindow& window) {
	window.draw(freeConvex);
}

void DrawableLine::setupLine(glm::vec2 pointA, glm::vec2 pointB, float width){

	vec2 direction = pointB - pointA;

	// if points are too close, then make "random" direction that will not break math
	if (isZero(glm::length(direction)))
		direction = {0.00001, 0.00001};

	vec2 perpendicular;

	if (isZero(direction.x)) 
		perpendicular = { 1, - direction.x / direction.y };
	else
		perpendicular = { -direction.y / direction.x, 1 };

	perpendicular = glm::normalize(perpendicular);
	vec2 halfDirectedOffset = perpendicular * (width / 2.f);

	freeConvex.setPoint(0, convert(pointA - halfDirectedOffset));
	freeConvex.setPoint(1, convert(pointA + halfDirectedOffset));
	freeConvex.setPoint(2, convert(pointB + halfDirectedOffset));
	freeConvex.setPoint(3, convert(pointB - halfDirectedOffset));
}

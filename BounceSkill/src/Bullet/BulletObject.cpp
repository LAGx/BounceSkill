#include "BulletObject.h"
#include "../Kernel/Math.h"


BulletObject::BulletObject(const StartBulletInfo& info) 
	: shape(drawableRadius, drawableSegments)
	, position(info.position) {

	shape.setPosition(convert(info.position));
	shape.setFillColor(mainColor);
	shape.setOutlineThickness(outlineSize);
	shape.setOutlineColor(outlineColor);

	glm::vec2 normalizedDirection = glm::normalize(info.direction);
	speed = normalizedDirection * info.speed;
}


void BulletObject::render(sf::RenderWindow& window){
	shape.setPosition(convert(position));
	window.draw(shape);
}


void BulletObject::simulate(const TimeInfo& time){
	glm::vec2 currentDeltaMove = speed * time.delta;
	position += currentDeltaMove;
}

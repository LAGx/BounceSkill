#include "BulletObject.h"
#include "../Kernel/Math.h"
#include "../Game/GameManager.h"

const sf::Color BulletObject::mainColor = { 120, 25, 50, 255 };
const sf::Color BulletObject::outlineColor = { 225, 50, 150, 255 };
const float BulletObject::outlineSize = -1.f;
const float BulletObject::drawableRadius = 3.f;
const float BulletObject::drawableSegments = 12.f;
const ClassId BulletObject::gameClassId = 2;


BulletObject::BulletObject(const StartBulletInfo& info) 
	: shape(drawableRadius, drawableSegments)
	, position(info.position) {

	shape.setPosition(convert(info.position));
	shape.setFillColor(mainColor);
	shape.setOutlineThickness(outlineSize);
	shape.setOutlineColor(outlineColor);

	glm::vec2 normalizedDirection = glm::normalize(info.direction);
	speed = normalizedDirection * info.speed;

	gameManager.collisionManager->registerListener(this);
}

BulletObject::~BulletObject() {
	gameManager.collisionManager->unregisterListener(this);
}

void BulletObject::render(sf::RenderWindow& window) const{
	window.draw(shape);
}


void BulletObject::simulate(const TimeInfo& time){
	glm::vec2 currentDeltaMove = speed * time.delta;
	position += currentDeltaMove;
	shape.setPosition(convert(position));
}

ClassId BulletObject::getClassId() const{
	return gameClassId;
}

ICollider* BulletObject::getCollider() const{
	return ;
}

void BulletObject::onCollisionDetection(ICollider* colliderA, ICollider* colliderB, const CollisionInfo& info){
	
}

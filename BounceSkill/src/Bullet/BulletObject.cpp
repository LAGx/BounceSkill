#include "BulletObject.h"
#include "../Kernel/Math.h"
#include "../Game/GameManager.h"
#include <iostream>
#include "../Wall/Wall.h"
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

const sf::Color BulletObject::mainColor = { 120, 25, 50, 255 };
const sf::Color BulletObject::outlineColor = { 225, 50, 150, 255 };
const float BulletObject::outlineSize = -1.f;
const float BulletObject::drawableRadius = 3.f;
const float BulletObject::drawableSegments = 12.f;
const ClassId BulletObject::gameClassId = 2;


BulletObject::BulletObject(const StartBulletInfo& info) 
	: shape(drawableRadius, drawableSegments)
	, position(info.position) 
{

	shape.setPosition(convert(info.position));
	shape.setFillColor(mainColor);
	shape.setOutlineThickness(outlineSize);
	shape.setOutlineColor(outlineColor);

	glm::vec2 normalizedDirection = glm::normalize(info.direction);
	speed = normalizedDirection * info.speed;

	deltaCollider.pointA = position;
	deltaCollider.pointB = position;
	deltaCollider.gameObject = this;
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

	// TODO line have to be longer on epsilon value for compensating calculation error
	deltaCollider.pointB = deltaCollider.pointA;
	deltaCollider.pointA = position;
}

ClassId BulletObject::getClassId() const{
	return gameClassId;
}

const ICollider* BulletObject::getCollider() const{
	return &deltaCollider;
}

void BulletObject::onCollisionDetection(const ICollider* colliderA, const ICollider* colliderB, const CollisionInfo& info) {

	Wall* wall = nullptr;

	if (colliderA->gameObject == this) {
		if (colliderB->gameObject->getClassId() == Wall::gameClassId) {
			wall = static_cast<Wall*>(colliderB->gameObject);
		}
	}

	if (!wall && colliderB->gameObject == this) {
		if (colliderA->gameObject->getClassId() == Wall::gameClassId) {
			wall = static_cast<Wall*>(colliderA->gameObject);
		}
	}

	if (wall) {
		auto wallData = wall->getWallData();
		reflectFromLine(wallData.pointA, wallData.pointB, info.touchPoint);
	}
}

void BulletObject::reflectFromLine(glm::vec2 pointA, glm::vec2 pointB, glm::vec2 touchPoint){
	auto lineDir = pointB - pointA;
	float currentSpeed = glm::length(this->speed);

	float side = glm::sign(glm::cross(glm::vec3{ lineDir, 0 }, glm::vec3{ speed, 0 }).z);
	float dirAndLineAngle = glm::acos(glm::dot(lineDir, this->speed) / (glm::length(lineDir) * currentSpeed));

	speed = glm::rotate(speed, -2 * side * dirAndLineAngle);

	float lengthOver = glm::length(touchPoint - deltaCollider.pointA);
	glm::vec2 direction = glm::normalize(speed);
	position = touchPoint + (direction * lengthOver);

	shape.setPosition(convert(position));
	deltaCollider.pointB = position; // to avoid double collision
	deltaCollider.pointA = position;
}
#pragma once
#include "../Kernel/IGameObject.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "StartBulletInfo.h"
#include "../Kernel/Collision/CollisionDetectorManager.h"
#include "../Kernel/Collision/Collider/ColliderLineTwoPoint.h"

// Assuume that bullet phisically is a line of two points between current point and a point on a previuos frame
class BulletObject : public IGameObject, ICollisionListener {
public:
	BulletObject() = delete;
	BulletObject(const StartBulletInfo& info);
	~BulletObject();

	// IGameObject
	void render(sf::RenderWindow& window) const override;
	void simulate(const TimeInfo& time) override;
	ClassId getClassId() const override;
	const ICollider* getCollider() const override;

	// ICollisionListener
	void onCollisionDetection(const ICollider* colliderA, const ICollider* colliderB, const CollisionInfo& info);

public:
	static const sf::Color mainColor;
	static const sf::Color outlineColor;
	static const float outlineSize;
	static const float drawableRadius;
	static const float drawableSegments;
	static const ClassId gameClassId;
private:
	void reflectFromLine(glm::vec2 pointA, glm::vec2 pointB, glm::vec2 touchPoint);

private:
	sf::CircleShape shape;
	DynamicColliderLineTwoPoint deltaCollider;

	// TODO: move inertianl phisic calclution to an abstract class 
	glm::vec2 position;
	glm::vec2 speed;
};
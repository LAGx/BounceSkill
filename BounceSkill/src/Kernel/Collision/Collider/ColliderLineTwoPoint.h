#pragma once
#include "ICollider.h"
#include <glm/vec2.hpp>

class ColliderLineTwoPoint : public ICollider {
public:
	ColliderLineTwoPoint(glm::vec2 _pointA, glm::vec2 _pointB);

	ClassColliderNick getClassColliderNick() const override;
	bool validate() const;

public: 
	const static ClassColliderNick ColliderNickStaticVariableName;
	glm::vec2 pointA = { 0, 0};
	glm::vec2 pointB = { 0, 0};
};


class StaticColliderLineTwoPoint : public ColliderLineTwoPoint {
public:
	using ColliderLineTwoPoint::ColliderLineTwoPoint;

	bool isStatic() const {
		return true;
	}
};


class DynamicColliderLineTwoPoint : public ColliderLineTwoPoint {
public:
	using ColliderLineTwoPoint::ColliderLineTwoPoint;

	bool isStatic() const {
		return false;
	}
};
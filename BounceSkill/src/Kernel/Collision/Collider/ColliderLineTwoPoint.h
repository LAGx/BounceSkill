#pragma once
#include "ICollider.h"
#include <glm/vec2.hpp>

class ColliderLineTwoPoint : public ICollider {
public:

	ClassColliderNick getClassColliderNick() const override;
	bool validate() const;

public: 
	const static ClassColliderNick ColliderNickStaticVariableName;
	glm::vec2 pointA = { 0, 0};
	glm::vec2 pointB = { 0, 0};
};
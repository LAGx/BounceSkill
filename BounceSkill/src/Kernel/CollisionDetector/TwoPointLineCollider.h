#pragma once
#include "CollisionDetector.h"


class TwoPointLineCollider : ICollider {
public:
	ClassColliderNick getClassColliderNick() const override;
	bool detectionMethod(ICollider*, CollisionInfo&) override;

	const static ClassColliderNick ClassColliderNickVariableName;
};
#pragma once
#include "ICollisionDetector.h"
#include "../Collider/ColliderLineTwoPoint.h"

class CollisionDetectorLineToLine : public ICollisionDetector {
public:
	ClassColliderNickPair getSupportedNickPair() const override;
	bool detectionMethod(const ICollider* colliderA, const ICollider* colliderB, CollisionInfo& info) override;
};
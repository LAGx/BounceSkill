#pragma once
#include "../CollisionTypes.h"
#include "../Collider/ICollider.h"

// CollisionDetector has metod for detecting only one pair of types colliders 
class ICollisionDetector {
public:
	virtual ClassColliderNickPair getSupportedNickPair() const = 0;
	virtual bool detectionMethod(const ICollider* colliderA, const ICollider* colliderB, CollisionInfo& info) = 0;
};
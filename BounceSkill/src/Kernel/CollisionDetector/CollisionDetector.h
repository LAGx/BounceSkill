#pragma once
#include "../../ExternalCode/ListenerManager.h"
#include <glm/vec2.hpp>

// ICollider realization class require classColliderNick static variable defining;
#define ClassColliderNickVariableName classColliderNick
#define SAFE_COLLIDER_UPCAST(upcastClassName, obj) upcastClassName##::classColliderNick == obj.getClassColliderNick() ? static_cast<upcastClassName*>(obj) : nullptr

typedef unsigned long long ClassColliderNick;

struct CollisionInfo {
	glm::vec2 touchPoint = {0, 0};
};

class ICollider {
public:
	virtual ClassColliderNick getClassColliderNick() const = 0;
	virtual bool detectionMethod(ICollider*, CollisionInfo&) = 0;
};

class ICollisionListener {
public:
	void onCollisionDetection(ICollider* colliderA, ICollider* colliderB, const CollisionInfo& info);
};

class CollisionDetector: ListenerManager<ICollisionListener> {
public:
	void update();
	void registerObject(ICollider*);
	void unregisterObject(ICollider*);

};
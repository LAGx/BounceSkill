#pragma once
#include "../../ExternalCode/ListenerManager.h"
#include <glm/vec2.hpp>
#include "Collider/ICollider.h"
#include <vector>
#include "Detector/ICollisionDetector.h"

class ICollisionListener {
public:
	virtual void onCollisionDetection(ICollider* colliderA, ICollider* colliderB, const CollisionInfo& info) = 0;
};


class CollisionDetectorManager: public ListenerManager<ICollisionListener> {
public:
	CollisionDetectorManager();
	~CollisionDetectorManager();

	void update();
	void registerObject(ICollider*);
	void unregisterObject(ICollider*);

public:
	std::vector<ICollider*> colliders;

public:
	ICollisionDetector* findDetector(const ClassColliderNickPair&) const;

private:
	std::vector<ICollisionDetector*> collisionDetectorList;
};
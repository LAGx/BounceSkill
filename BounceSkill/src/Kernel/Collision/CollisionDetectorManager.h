#pragma once
#include "../../ExternalCode/ListenerManager.h"
#include <glm/vec2.hpp>
#include "Collider/ICollider.h"
#include <vector>
#include "Detector/ICollisionDetector.h"
#include "Detector/CollisionDetectorLineToLine.h"

class ICollisionListener {
public:
	virtual void onCollisionDetection(const ICollider* colliderA, const ICollider* colliderB, const CollisionInfo& info) = 0;
};


class CollisionDetectorManager: public ListenerManager<ICollisionListener> {
public:
	CollisionDetectorManager();
	~CollisionDetectorManager();

	void update();
	void registerObject(const ICollider*);
	void unregisterObject(const ICollider*);

public:
	std::vector<const ICollider*> colliders;

public:
	ICollisionDetector* findDetector(const ClassColliderNickPair&) const;

private:
	CollisionDetectorLineToLine lineToLineDetector;
	std::vector<ICollisionDetector*> collisionDetectorList;
};
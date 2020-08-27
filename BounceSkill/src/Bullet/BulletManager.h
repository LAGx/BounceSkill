#pragma once
#include "StartBulletInfo.h"
#include "../Kernel/Collision/CollisionDetectorManager.h"

class BulletManager: public ICollisionListener {
public:
	BulletManager();
	~BulletManager();

	void Update(float globalTime);
	// thread safe. blocking for not main thread
	void Fire(const StartBulletInfo& bullet);

	// ICollisionListener
	void onCollisionDetection(const ICollider* colliderA, const ICollider* colliderB, const CollisionInfo& info) override;

};
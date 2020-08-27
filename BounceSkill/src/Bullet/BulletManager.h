#pragma once
#include "BulletInfo.h"
#include "../Kernel/Collision/CollisionDetectorManager.h"
#include <vector>
#include <mutex>

class BulletManager: public ICollisionListener {
public:
	BulletManager();
	~BulletManager();

	void Update(float globalTime);
	// thread safe. blocking for not main thread
	void Fire(const StartBulletInfo& bullet);

	// ICollisionListener
	void onCollisionDetection(const ICollider* colliderA, const ICollider* colliderB, const CollisionInfo& info) override;

private:
	IGameObject* createBullet(const StartBulletInfo& info);
	void deleteBullet(IGameObject*);
	void utilizeSharedBuffer();

private:
	std::vector<ManagingBulletInfo> managingBullets;
	std::vector<StartBulletInfo> sharedBufferInfo;
	std::mutex bufferInfo_mut;
};
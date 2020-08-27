#pragma once
#include "BulletInfo.h"
#include "../Kernel/Collision/CollisionDetectorManager.h"
#include <vector>
#include <condition_variable>
#include <mutex>
#include <thread>

class BulletManager: public ICollisionListener {
public:
	BulletManager();
	~BulletManager();

	void Update(float globalTime);

	// thread safe
	// blocking
	// Warning: do not to use in main thread
	void SyncFire(const StartBulletInfo& bullet);

	// Method for main thread
	void Fire(const StartBulletInfo& bullet);

	// ICollisionListener
	void onCollisionDetection(const ICollider* colliderA, const ICollider* colliderB, const CollisionInfo& info) override;

	bool forceGetSharedResource() const;

private:
	IGameObject* createBullet(const StartBulletInfo& info);
	void deleteBullet(IGameObject*);
	void utilizeSharedBuffer();

private:
	std::vector<ManagingBulletInfo> managingBullets;
	std::vector<StartBulletInfo> sharedBufferInfo;

	std::mutex bufferInfo_mut;
	unsigned int failsToGetSharedResourceByMainThread = 0;
	const unsigned int limitToForceGettingResource = 5;

	std::mutex forceSync_mut;
	std::condition_variable forceSync_cv;
};
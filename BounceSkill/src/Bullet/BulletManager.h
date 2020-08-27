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

	// It requires in case when the main thread can`t get the resource for the long period of time.
	// After that, the algorithm locks the resource until the main thread performs required operations.std::mutex bufferInfo_mut;
	std::mutex bufferInfo_mut;
	std::condition_variable forceSync_cv;
	std::atomic<unsigned int> sharedBufferSize = 0;
	unsigned int failsToGetSharedResourceByMainThread = 0;
	const unsigned int limitToForceGettingResource = 5;
};
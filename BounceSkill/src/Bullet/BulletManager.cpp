#pragma once
#include "BulletManager.h"
#include "../Kernel/IGameObject.h"
#include "../Wall/Wall.h"
#include "BulletObject.h"
#include "../Game/GameManager.h"

BulletManager::BulletManager(){
	gameManager.collisionManager->registerListener(this);
}

BulletManager::~BulletManager(){
	gameManager.collisionManager->unregisterListener(this);
}

void BulletManager::Update(float globalTime) {

	utilizeSharedBuffer();

	for (int i = 0; i < managingBullets.size(); ++i) {
		auto& info = managingBullets[i];

		if (globalTime > info.startInfo.lifeTime) {
			deleteBullet(info.obj);
			managingBullets.erase(managingBullets.begin() + i);
			--i;
			continue;
		}

		if (info.obj == nullptr && globalTime > info.startInfo.timeToSpawn) {
			info.obj = createBullet(info.startInfo);
		}
	}
}

void BulletManager::utilizeSharedBuffer() {
	if (sharedBufferInfo.size() == 0)
		return;

	bool locked = bufferInfo_mut.try_lock();
	if (locked) {
		for (const auto& stInfo : sharedBufferInfo) {
			managingBullets.push_back({ stInfo });
		}
		sharedBufferInfo.clear();
		failsToGetSharedResourceByMainThread = 0;
		bufferInfo_mut.unlock();
		forceSync_cv.notify_all();
	}
	else {
		++failsToGetSharedResourceByMainThread;
	}
}

void BulletManager::SyncFire(const StartBulletInfo& bullet) {
	std::unique_lock<std::mutex> forceWait(forceSync_mut);

	const auto waitPredicate = [this]() -> bool{
		return !this->forceGetSharedResource();
	};

	forceSync_cv.wait(forceWait, waitPredicate);

	bufferInfo_mut.lock();
	sharedBufferInfo.push_back(bullet);
	bufferInfo_mut.unlock();
}

void BulletManager::Fire(const StartBulletInfo& bullet){
	managingBullets.push_back({ bullet });
}

void BulletManager::onCollisionDetection(const ICollider* colliderA, const ICollider* colliderB, const CollisionInfo& info){
	IGameObject* objA = colliderA->gameObject;
	IGameObject* objB = colliderB->gameObject;

	if (!objA || !objB)
		return;

	const ClassId idA = objA->getClassId();
	const ClassId idB = objB->getClassId();

	if (idA == Wall::gameClassId && idB == BulletObject::gameClassId){
		gameManager.deleteGameObject(objA);
	}
	else if (idA == BulletObject::gameClassId && idB == Wall::gameClassId) {
		gameManager.deleteGameObject(objB);
	}
}

IGameObject* BulletManager::createBullet(const StartBulletInfo& info){
	auto bullet = new BulletObject(info);
	gameManager.spawnGameObject(bullet);
	return bullet;
}

void BulletManager::deleteBullet(IGameObject* obj){
	if (obj != nullptr)
		gameManager.deleteGameObject(obj);
}


bool BulletManager::forceGetSharedResource() const {
	return failsToGetSharedResourceByMainThread >= limitToForceGettingResource;
}
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

}


void BulletManager::Fire(const StartBulletInfo& bullet) {

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

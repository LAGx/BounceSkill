#include "CollisionDetectorManager.h"
#include <algorithm>
#include "Detector/CollisionDetectorLineToLine.h"

CollisionDetectorManager::CollisionDetectorManager() : 
	collisionDetectorList({
		new CollisionDetectorLineToLine()
		})
	{}


CollisionDetectorManager::~CollisionDetectorManager()
{
	for (auto el : collisionDetectorList)
		delete el;
}

void CollisionDetectorManager::update(){
	for (int i = 0; i < colliders.size(); ++i) {
		for (int j = i + 1; j < colliders.size(); ++j) {
			auto colliderA = colliders[i];
			auto colliderB = colliders[j];

			if (colliderA->isStatic() && colliderB->isStatic())
				continue;

			ClassColliderNickPair nickPair = {colliderA->getClassColliderNick(), colliderB->getClassColliderNick()};
			auto detector = findDetector(nickPair);

			if (detector) {
				CollisionInfo info;
				detector->detectionMethod(colliderA, colliderB, info);
				InvokeListener(&ICollisionListener::onCollisionDetection, colliderA, colliderB, info);
			}
			else {
				assert("can`t find collision detector for such colliders.");
			}
		}
	}
}


void CollisionDetectorManager::registerObject(const ICollider* collider){
	auto found = std::find(colliders.begin(), colliders.end(), collider);
	
	if (found == colliders.end())
		colliders.push_back(collider);
}


void CollisionDetectorManager::unregisterObject(const ICollider* collider){
	auto found = std::find(colliders.begin(), colliders.end(), collider);

	if (found != colliders.end())
		colliders.erase(found);
}


ICollisionDetector* CollisionDetectorManager::findDetector(const ClassColliderNickPair& nickPair) const{
	auto found = std::find_if(collisionDetectorList.begin(), collisionDetectorList.end(), [&nickPair](const ICollisionDetector* detector) -> bool {
		return detector->getSupportedNickPair() == nickPair;
		});

	return found != collisionDetectorList.end() ? *found : nullptr;
}

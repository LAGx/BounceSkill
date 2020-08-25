#include "CollisionDetectorLineToLine.h"
#include <glm/glm.hpp>

ClassColliderNickPair CollisionDetectorLineToLine::getSupportedNickPair() const
{
	return { GetColliderNickName(ColliderLineTwoPoint), GetColliderNickName(ColliderLineTwoPoint)};
}

bool CollisionDetectorLineToLine::detectionMethod(const ICollider* colliderA, const ICollider* colliderB, CollisionInfo& info)
{
	if (getSupportedNickPair() != ClassColliderNickPair {colliderA->getClassColliderNick(), colliderB->getClassColliderNick()})
		assert("CollisionDetectorLineToLine does not support this collider types");

	const ColliderLineTwoPoint* castedColliderA = static_cast<const ColliderLineTwoPoint*>(colliderA);
	const ColliderLineTwoPoint* castedColliderB = static_cast<const ColliderLineTwoPoint*>(colliderB);

	glm::vec3 cut1 = { castedColliderA->pointB - castedColliderA->pointA, 0 };
	glm::vec3 cut2 = { castedColliderB->pointB - castedColliderB->pointA, 0 };

	glm::vec3 prod1 = glm::cross(cut1, { (castedColliderB->pointA - castedColliderA->pointA), 0 });
	glm::vec3 prod2 = glm::cross(cut1, { (castedColliderB->pointB - castedColliderA->pointA), 0 });

	if (glm::sign(prod1.z) == glm::sign(prod2.z) || (prod1.z == 0) || (prod2.z == 0))
		return false;

	prod1 = glm::cross(cut2, { (castedColliderA->pointA - castedColliderB->pointA), 0 });
	prod2 = glm::cross(cut2, { (castedColliderA->pointB - castedColliderB->pointA), 0 });

	if (glm::sign(prod1.z) == glm::sign(prod2.z) || (prod1.z == 0) || (prod2.z == 0))
		return false;

	info.touchPoint.x = castedColliderA->pointA.x + cut1.x * fabs(prod1.z) / fabs(prod2.z - prod1.z);
	info.touchPoint.y = castedColliderA->pointA.y + cut1.y * fabs(prod1.z) / fabs(prod2.z - prod1.z);

	return true;
}

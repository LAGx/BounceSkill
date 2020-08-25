#include "ColliderLineTwoPoint.h"
#include "../../Math.h"
#include "glm/gtx/norm.hpp"

const ClassColliderNick ColliderLineTwoPoint::colliderNickName = 10;

ClassColliderNick ColliderLineTwoPoint::getClassColliderNick() const{
    return colliderNickName;
}

bool ColliderLineTwoPoint::validate() const{
	return !isZero(glm::length(pointA - pointB));
}

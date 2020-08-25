#include "ColliderLineTwoPoint.h"
#include "../../Math.h"
#include "glm/gtx/norm.hpp"

const ClassColliderNick ColliderLineTwoPoint::colliderNickName = 10;

ColliderLineTwoPoint::ColliderLineTwoPoint(glm::vec2 _pointA, glm::vec2 _pointB)
	: pointA(_pointA)
	,pointB(_pointB)
	{}

ClassColliderNick ColliderLineTwoPoint::getClassColliderNick() const{
    return colliderNickName;
}

bool ColliderLineTwoPoint::validate() const{
	return !isZero(glm::length(pointA - pointB));
}

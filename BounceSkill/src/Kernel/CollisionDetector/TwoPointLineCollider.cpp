#include "TwoPointLineCollider.h"

ClassColliderNick TwoPointLineCollider::getClassColliderNick() const
{
    return classColliderNick;
}

bool TwoPointLineCollider::detectionMethod(ICollider* collider, CollisionInfo& info)
{
	TwoPointLineCollider* another = SAFE_COLLIDER_UPCAST(TwoPointLineCollider, collider);

	vector<T, 3> cut1(v12 - v11), cut2(v22 - v21);
	vector<T, 3> prod1, prod2;

	prod1 = cross(cut1 * (v21 - v11));
	prod2 = cross(cut1 * (v22 - v11));

	if (sign(prod1[Z]) == sign(prod2[Z]) || (prod1[Z] == 0) || (prod2[Z] == 0))
		return false;

	prod1 = cross(cut2 * (v11 - v21));
	prod2 = cross(cut2 * (v12 - v21));

	if (sign(prod1[Z]) == sign(prod2[Z]) || (prod1[Z] == 0) || (prod2[Z] == 0))
		return false;

	if (crossing) {
		(*crossing)[X] = v11[X] + cut1[X] * fabs(prod1[Z]) / fabs(prod2[Z] - prod1[Z]);
		(*crossing)[Y] = v11[Y] + cut1[Y] * fabs(prod1[Z]) / fabs(prod2[Z] - prod1[Z]);
	}

	return true;
}
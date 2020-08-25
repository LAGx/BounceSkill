#include "CollisionTypes.h"

bool ClassColliderNickPair::operator==(const ClassColliderNickPair& another) const
{
	return (nickA == another.nickA && nickB == another.nickB) ||
		(nickA == another.nickB && nickB == another.nickA);
}

bool ClassColliderNickPair::operator!=(const ClassColliderNickPair& another) const
{
	return !(*this == another);
}

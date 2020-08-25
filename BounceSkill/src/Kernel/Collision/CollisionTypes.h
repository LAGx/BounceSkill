#pragma once
#include <glm/vec2.hpp>

typedef unsigned long long ClassColliderNick;

struct ClassColliderNickPair {
	ClassColliderNick nickA;
	ClassColliderNick nickB;

	bool operator==(const ClassColliderNickPair& another) const;
	bool operator!=(const ClassColliderNickPair& another) const;
};

struct CollisionInfo {
	glm::vec2 touchPoint = { 0, 0 };
};
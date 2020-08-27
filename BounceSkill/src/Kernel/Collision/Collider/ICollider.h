#pragma once
#include "../CollisionTypes.h"

#define ColliderNickStaticVariableName colliderNickName
#define GetColliderNickName(className) className##::colliderNickName

class IGameObject;

class ICollider {
public:
	// static objects can`t move and collide with each other
	virtual bool isStatic() const = 0;
	virtual ClassColliderNick getClassColliderNick() const = 0;
	virtual ~ICollider() {};

	// needs for attaching game object to collider on collision event
	IGameObject* gameObject = nullptr;
};
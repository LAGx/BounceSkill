#pragma once
#include "Collision/Collider/ICollider.h"
#include "IDrawable.h"
#include "ISimulatable.h"

typedef unsigned long long ClassId;

struct IGameObject: public IDrawable, public ISimulatable{
	virtual ClassId getClassId() const = 0;
	virtual ICollider* getCollider() const { return nullptr; }
};
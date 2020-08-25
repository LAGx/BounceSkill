#pragma once
#include "../Kernel/IGameObject.h"
#include "../Kernel/Primitives/DrawableLine.h"
#include "../Kernel/Collision/Collider/ColliderLineTwoPoint.h"
#include "WallData.h"

// Assuume that wall phisically is a line
class Wall: public IGameObject {
public:
	Wall(const WallData&);

	// IGameObject
	void render(sf::RenderWindow&) const override;
	ClassId getClassId() const override;
	void simulate(const TimeInfo&) override;
	const ICollider* getCollider() const override;

public:
	const static ClassId gameClassId;
private:
	StaticColliderLineTwoPoint collider;
	const DrawableLine drawableLine;
};
#pragma once
#include "StartBulletInfo.h"

class BulletManager {
public:

	void Update(float globalTime);

	void Fire(const StartBulletInfo& bullet);
};
#pragma once
#include <vector>
#include "../Wall/WallData.h"
#include "../Bullet/BulletInfo.h"

class SceneData {
public:
	std::vector<WallData> walls;
	std::vector<StartBulletInfo> bullets;
};
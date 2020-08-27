#pragma once
#include <glm/glm.hpp>
#include "../Kernel/IGameObject.h"


struct StartBulletInfo {
	glm::vec2 position = {0, 0};
	glm::vec2 direction = {0, 0};
	float speed = 0.0f; //< pixels per seconds
	float timeToSpawn = 0;
	float lifeTime = 0;
};


struct ManagingBulletInfo{
	StartBulletInfo startInfo;
	IGameObject* obj = nullptr;
};

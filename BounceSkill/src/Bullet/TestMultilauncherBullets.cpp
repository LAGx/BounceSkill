#include "TestMultilauncherBullets.h"
#include "../Game/GameManager.h"
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>


void TestMultilauncherBullets::init(){
	for (int i = 0; i < MULTILAUNCHER_THREAD_AMOUNT; ++i) {
		threads.push_back(std::thread(&TestMultilauncherBullets::launcher, this, i));
	}
}


void TestMultilauncherBullets::cleanup(){
	for (int i = 0; i < MULTILAUNCHER_THREAD_AMOUNT; ++i) {
		if (threads[i].joinable()) {
			threads[i].join();
		}
	}
}

void TestMultilauncherBullets::launcher(int i) {
	std::this_thread::sleep_for(std::chrono::seconds(3));
	const int bulletsAmount = 10;

	for (int j = 0; j < bulletsAmount; ++j) {
		StartBulletInfo info;
		info.direction = glm::rotate(glm::vec2{ 1.f, 1.f }, 2.f * glm::pi<float>() * ((float)j/ bulletsAmount));
		info.lifeTime = 20.0;
		info.position = {i * 100.f + 100.f, 250.f};
		info.speed = 20.f * (i + 1);
		info.timeToSpawn = 4.0;

		gameManager.bulletManager->SyncFire(info);
	}
}
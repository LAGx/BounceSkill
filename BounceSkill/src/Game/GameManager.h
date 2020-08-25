#pragma once
#include "../Kernel/Collision/CollisionDetectorManager.h"
#include <SFML/Graphics.hpp>
#include "../ExternalCode/FPSController.h"
#include "SceneData.h"
#include "../Kernel/IGameObject.h"
#include "../Bullet/BulletManager.h"

class GameManager {
public:
	void init();
	void spawnScene(const SceneData&);
	void run();
	void cleanup();

	~GameManager();

public:
	std::unique_ptr<CollisionDetectorManager> collisionManager;

private:
	void onUpdate();

private:
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<BulletManager> bulletManager;
	rofle::FPSController fpsController;
	TimeInfo currentTimeInfo;

	std::vector<IGameObject*> gameObjects;
};

extern GameManager gameManager;
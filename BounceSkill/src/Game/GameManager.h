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

	// owner of resource becomes GameManager
	void spawnGameObject(IGameObject*);
	void deleteGameObject(IGameObject*);

	~GameManager();

public:
	std::unique_ptr<CollisionDetectorManager> collisionManager;

private:
	void onUpdate();
	void postUpdate();

private:
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<BulletManager> bulletManager;
	rofle::FPSController fpsController;
	TimeInfo currentTimeInfo;

	std::vector<IGameObject*> gameObjects;
	std::vector<IGameObject*> trashedGameObjects;
};

extern GameManager gameManager;
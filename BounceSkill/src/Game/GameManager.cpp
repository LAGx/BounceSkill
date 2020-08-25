#include "GameManager.h"
#include "../Wall/Wall.h"

GameManager gameManager;

void GameManager::init(){
	window.reset(new sf::RenderWindow(sf::VideoMode(900, 500), "Tupa adixau, realno..."));
	collisionManager.reset(new CollisionDetectorManager());
        bulletManager.reset(new BulletManager());
        fpsController.setTargetFPS(60);
}


void GameManager::spawnScene(const SceneData& data) {
        // spawn walls 
        for (const auto& wallData : data.walls) {
                auto obj = new Wall(wallData);

                if (auto collider = obj->getCollider())
                        collisionManager->registerObject(collider);
                gameObjects.emplace_back(obj);
        }
}


void GameManager::run(){

        while (window->isOpen())
        {
                sf::Event event;
                while (window->pollEvent(event))
                {
                        if (event.type == sf::Event::Closed)
                                window->close();
                }

                window->clear({ 15, 18, 18, 255 });

                currentTimeInfo.delta = fpsController.getFrameDelta().GetSeconds<float>();
                currentTimeInfo.global += currentTimeInfo.delta;

                onUpdate();

                window->display();
                window->setTitle(std::string("FPS: ") + std::to_string(fpsController.getSmoothFPS()));
                fpsController.seek();
        }
}

void GameManager::cleanup(){
        for (auto& obj : gameObjects){
                if (auto collider = obj->getCollider())
                        collisionManager->unregisterObject(collider);
                delete obj;
        }
        gameObjects.clear();
}

GameManager::~GameManager(){
        cleanup();
}

void GameManager::onUpdate(){
        for (auto obj : gameObjects) {
                obj->simulate(currentTimeInfo);
                obj->render(*window);
        }

        bulletManager->Update(currentTimeInfo.global);
}

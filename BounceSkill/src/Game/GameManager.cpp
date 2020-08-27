#include "GameManager.h"
#include "../Wall/Wall.h"
#include "../Bullet/BulletObject.h"

GameManager gameManager;

void GameManager::init(){
	window.reset(new sf::RenderWindow(sf::VideoMode(900, 500), "Tupa adixau, realno..."));
	collisionManager.reset(new CollisionDetectorManager());
        bulletManager.reset(new BulletManager());
        fpsController.setTargetFPS(60);
}


void GameManager::spawnScene(const SceneData& data) {
        // spawn bullets
        for (const auto& bulletInfo : data.bullets) {
                bulletManager->Fire(bulletInfo);
        }

        // spawn walls 
        for (const auto& wallData : data.walls) {
                auto obj = new Wall(wallData);
                spawnGameObject(obj);
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
                window->setTitle(std::string("FPS: ") + std::to_string(fpsController.getSmoothFPS()) + "  | global: " + std::to_string(currentTimeInfo.global) );
                fpsController.seek();
        }
}

void GameManager::cleanup(){
        postUpdate();

        for (auto& obj : gameObjects){
                if (auto collider = obj->getCollider())
                        collisionManager->unregisterObject(collider);
                delete obj;
        }
        gameObjects.clear();
        window.release();
}

void GameManager::spawnGameObject(IGameObject* obj){
        if (auto collider = obj->getCollider())
                collisionManager->registerObject(collider);
        gameObjects.emplace_back(obj);
}

void GameManager::deleteGameObject(IGameObject* obj){
        auto found = std::find(gameObjects.begin(), gameObjects.end(), obj);

        if (found != gameObjects.end()) {
                trashedGameObjects.push_back(*found);
        }
}

GameManager::~GameManager(){
        cleanup();
}

void GameManager::onUpdate(){
        for (auto obj : gameObjects) {
                collisionManager->update();
                obj->simulate(currentTimeInfo);
                obj->render(*window);
        }

        bulletManager->Update(currentTimeInfo.global);
        postUpdate();
}

void GameManager::postUpdate(){
        // delete trash

        for (auto obj : trashedGameObjects) {
                auto found = std::find(gameObjects.begin(), gameObjects.end(), obj);

                if (found != gameObjects.end()) {
                        if (auto collider = (*found)->getCollider())
                                collisionManager->unregisterObject(collider);
                        delete (*found);

                        gameObjects.erase(found);
                }
        }
        
        trashedGameObjects.clear();
}

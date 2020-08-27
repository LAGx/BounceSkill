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
        float bullet_speed = 120;

        // spawn bullet
        StartBulletInfo bulletInfo;
        bulletInfo.direction = {2, 1};
        bulletInfo.position = {300, 100};
        bulletInfo.speed = bullet_speed;
        IGameObject* bullet = new BulletObject(bulletInfo);
        spawnGameObject(bullet);
        
        StartBulletInfo bulletInfo2;
        bulletInfo2.direction = { 2, -1 };
        bulletInfo2.position = { 300, 350 };
        bulletInfo2.speed = bullet_speed;
        IGameObject* bullet2 = new BulletObject(bulletInfo2);
        spawnGameObject(bullet2);
        
        StartBulletInfo bulletInfo3;
        bulletInfo3.direction = { -0.1, 1 };
        bulletInfo3.position = { 500, 50 };
        bulletInfo3.speed = bullet_speed;
        IGameObject* bullet3 = new BulletObject(bulletInfo3);
        spawnGameObject(bullet3);
        
        StartBulletInfo bulletInfo4;
        bulletInfo4.direction = { -3, -1 };
        bulletInfo4.position = { 500, 350 };
        bulletInfo4.speed = bullet_speed;
        IGameObject* bullet4 = new BulletObject(bulletInfo4);
        spawnGameObject(bullet4);

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

                if (auto collider = obj->getCollider())
                        collisionManager->unregisterObject(collider);
                delete obj;

                gameObjects.erase(found);
        }
        
        trashedGameObjects.clear();
}

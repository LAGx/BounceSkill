#include "Game/GameManager.h"


float rand(float min, float max) {
        return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

SceneData getSceneData() {
        SceneData data;

        auto generatorX = []() -> float {
                return rand(0, 900);
        };
        
        auto generatorY = []() -> float {
                return rand(0, 500);
        };
        
        for (int i = 0; i < 300; ++i) {
                data.walls.push_back({ {generatorX(), generatorY()}, {generatorX(), generatorY()} });
        }

        //data.walls = {
        //        { {10, 10}, {100, 100}},
        //        { {200, 20}, {50, 350}},
        //        { {400, 100}, {450, 120}},
        //        { {600, 400}, {350, 450}},
        //        { {650, 450}, {350, 455}},
        //        { {140, 16}, {88, 200}},
        //        { {350, 140}, {140, 350}},
        //        { {150, 20}, {400, 350}}
        //};

        //data.walls = {
        //        {  {50, 400} , {600, 50}}
        //};

        return data;
}

int main() {
        srand(static_cast <unsigned> (time(0)));

        gameManager.init();
        gameManager.spawnScene(getSceneData());
        gameManager.run();
        gameManager.cleanup();

        return 0;
}
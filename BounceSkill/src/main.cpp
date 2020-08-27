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
        
        for (int i = 0; i < 1000; ++i) {
                data.walls.push_back({ {generatorX(), generatorY()}, {generatorX(), generatorY()} });
        }

        // for (int i = 0; i < 50; ++i) {
        //         data.bullets.push_back({
        //                 {450.0+(float)(i*10.0), 250},
        //                 {1, (float)(1.0+i)},
        //                 (float)(60.0 + i * 20),
        //                 i/2.0f + 2.0f,
        //                 i / 2.0f + 2.0f + 1.0f,
        //                 });
        // }

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
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
        
        for (int i = 0; i < 30; ++i) {
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

        for (int i = 0; i < 10; ++i) {
                data.bullets.push_back({
                        {300.0+(float)(i*10.0), 300},
                        {1, (float)(1.0+i)},
                        (float)(60.0+i),
                        0,
                        1000
                        });
        }

      //  data.bullets.push_back({
      //  {100, 100},
      //  {1, 1},
      //  30,
      //  3,
      //  4
      //          });
      //
      //  data.bullets.push_back({
      //  {200, 100},
      //  {1, 1},
      //  60,
      //  3,
      //  4
      //          });
      //
      //  data.bullets.push_back({
      //  {300, 100},
      //  {1, 1},
      //  80,
      //  0,
      //  1
      //          });
      //
      //  data.bullets.push_back({
      //  {400, 100},
      //  {1, 1},
      //  120,
      //  9,
      //  11
      //          });
      //
      //  data.bullets.push_back({
      //  {500, 100},
      //  {1, 1},
      //  1,
      //  0,
      //  10
      //          });
      //
      //  data.bullets.push_back({
      //  {600, 100},
      //  {1, 1},
      //  0,
      //  5,
      //  11
      //          });
      //
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
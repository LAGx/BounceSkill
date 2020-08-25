#include "Game/GameManager.h"


SceneData getSceneData() {
        SceneData data;

        data.walls = {
                { {10, 10}, {100, 100}},
                { {200, 20}, {50, 350}},
                { {400, 100}, {450, 120}},
                { {600, 400}, {350, 450}},
                { {650, 450}, {350, 455}},
                { {140, 16}, {88, 200}},
                { {350, 140}, {140, 350}},
                { {55, 89}, {112, 221}}
        };

        return data;
}

int main() {
        gameManager.init();
        gameManager.spawnScene(getSceneData());
        gameManager.run();
        gameManager.cleanup();

        return 0;
}
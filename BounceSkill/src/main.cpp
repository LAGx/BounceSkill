#include <SFML/Graphics.hpp>
#include "Kernel/Primitives/DrawableLine.h"
#include "Bullet/BulletObject.h"
#include "ExternalCode/FPSController.h"

int main()
{
        sf::RenderWindow window(sf::VideoMode(900, 500), "Tupa adixau, realno...");
        DrawableLine line1({ 200, 250 }, { 100, 200 }, 2, {100, 200, 100, 255});
        StartBulletInfo bulletInfo;
        bulletInfo.position = {100, 400};
        bulletInfo.direction = { 5, -2 };
        bulletInfo.speed = 5.f;
        BulletObject bullet(bulletInfo);
        //DrawableLine line2();
        //DrawableLine line2();
       
        //shape.setFillColor(sf::Color::Green);

        rofle::FPSController fpsController;
        fpsController.setTargetFPS(60);

        while (window.isOpen())
        {
                sf::Event event;
                while (window.pollEvent(event))
                {
                        if (event.type == sf::Event::Closed)
                                window.close();
                }

                window.clear({15, 18, 18, 255});

                bullet.render(window);
                bullet.simulate({0, fpsController.getFrameDelta().GetSeconds<float>()});
                line1.render(window);

                window.display();
                window.setTitle(std::string("FPS: ") + std::to_string(fpsController.getSmoothFPS()));
                fpsController.seek();
        }

        return 0;
}
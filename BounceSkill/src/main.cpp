#include <SFML/Graphics.hpp>
#include "Kernel/Primitives/DrawableLine.h"

int main()
{
        sf::RenderWindow window(sf::VideoMode(900, 500), "SFML works!");
        DrawableLine line1({ 200, 200 }, {200, 200}, 10, sf::Color::Magenta);
        //DrawableLine line2();
        //DrawableLine line2();

        sf::CircleShape shape(50.f);
        shape.setFillColor(sf::Color::Green);

        while (window.isOpen())
        {
                sf::Event event;
                while (window.pollEvent(event))
                {
                        if (event.type == sf::Event::Closed)
                                window.close();
                }

                window.clear();
                window.draw(shape);
                line1.render(window);
                window.display();
        }

        return 0;
}
#pragma once
#include "SFML/Graphics/RenderWindow.hpp"

struct IDrawable {
	virtual void render(sf::RenderWindow&) const = 0;
};
#pragma once

namespace sf {
	class RenderWindow;
}

struct IDrawable {
	virtual void render(sf::RenderWindow&) = 0;
};
#pragma once
#include "../Kernel/IDrawable.h"

// Assuume that wall phisically is a line
class Wall: IDrawable {
public:
	// IDrawable
	void render(sf::RenderWindow&) override;
};
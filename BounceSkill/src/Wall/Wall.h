#pragma once
#include "../Kernel/IDrawable.h"

class Wall: IDrawable {
public:
	// IDrawable
	void render(sf::RenderWindow&) override;
};
#pragma once
#include "../Kernel/IDrawable.h"
#include "../Kernel/ISimulatable.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "StartBulletInfo.h"

// Assuume that bullet phisically is a point
class BulletObject : IDrawable, ISimulatable {
public:
	BulletObject() = delete;
	BulletObject(const StartBulletInfo& info);

	// IDrawable
	void render(sf::RenderWindow& window) override;

	// ISimulatable
	void simulate(const TimeInfo& time) override;

public:
	const sf::Color mainColor = { 120, 25, 50, 255 };
	const sf::Color outlineColor = { 225, 50, 150, 255 };
	const float outlineSize = -1.f;
	const float drawableRadius = 3.f;
	const float drawableSegments = 12.f;
private:
	sf::CircleShape shape;

	// TODO: move inertianl phisic calclution to an abstract class 
	glm::vec2 position;
	glm::vec2 speed;
};

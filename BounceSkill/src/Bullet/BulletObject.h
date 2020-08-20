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
	static const sf::Color mainColor;
	static const sf::Color outlineColor;
	static const float outlineSize;
	static const float drawableRadius;
	static const float drawableSegments;
private:
	sf::CircleShape shape;

	// TODO: move inertianl phisic calclution to an abstract class 
	glm::vec2 position;
	glm::vec2 speed;
};

#include "Math.h"

bool isZero(float value) {
	return abs(value) <= std::numeric_limits<float>().epsilon();
}

sf::Vector2f convert(const glm::vec2& input) {
	return { input.x, input.y };
}


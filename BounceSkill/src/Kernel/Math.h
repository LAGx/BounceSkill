#pragma once
#include "glm/vec2.hpp"
#include "SFML/System/Vector2.hpp"
#include <limits>

bool isZero(float value);

sf::Vector2f convert(const glm::vec2& input);
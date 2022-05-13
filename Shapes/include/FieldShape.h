#pragma once
#include "SFML\Graphics.hpp"

struct FieldShape {
	static sf::Vector2f PreviousRealMousePosition;
	static sf::Vector2f PreviousViewCenter;
	static int Width;
	static int Height;
};

#include "Defaultshape.h"

sf::Vector2f DefaultShape::getPosition() {
    return sf::Vector2f(Width, Height);
}

sf::Vector2f DefaultShape::getSize() {
    return sf::Vector2f(X, Y);
}
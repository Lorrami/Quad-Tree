#pragma once

#include "SFML/Graphics.hpp"
#include "ShapesType.h"

struct DefaultShape {
    float Width{}, Height{};
    float X{}, Y{};
    ShapesType type = ShapesType::Default;

    virtual void Update(sf::RenderWindow *window) = 0;

    sf::Vector2f getPosition();
    sf::Vector2f getSize();
};
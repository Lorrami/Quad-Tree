#pragma once

#include "DefaultShape.h"

struct RectangleShape : public DefaultShape {
    explicit RectangleShape(float SizeX = 0.0f, float SizeY = 0.0f, float PositionX = 1.0f, float PositionY = 1.0f);

    void Update(sf::RenderWindow *window)override;
};
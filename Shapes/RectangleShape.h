#pragma once

#include "DefaultShape.h"

struct RectangleShape : public DefaultShape {
    explicit RectangleShape(float width = 0.0f, float height = 0.0f, float X = 1.0f, float Y = 1.0f);

    void Update(sf::RenderWindow *window)override;
};
#pragma once

#include "DefaultShape.h"

struct CircleShape : public DefaultShape {
    explicit CircleShape(float radius = 0.0f, float x = 1.0f, float y = 1.0f);

    void Update(sf::RenderWindow *window)override;
};

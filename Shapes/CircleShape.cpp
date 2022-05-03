#include <iostream>
#include "CircleShape.h"
#include "../Render2D.h"

CircleShape::CircleShape(float radius, float x, float y) {
    type = ShapesType::Circle;
    this->Width = radius;
    this->Height = radius;
    this->X = x;
    this->Y = y;
}

void CircleShape::Update(sf::RenderWindow *window) {
    Render2D::CircleDrawing(window, this);
}

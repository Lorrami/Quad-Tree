#include <iostream>
#include "RectangleShape.h"
#include "../Render2D.h"

RectangleShape::RectangleShape(float width, float height, float x, float y) {
    type = ShapesType::Rectangle;
    this->Width = width;
    this->Height = height;
    this->X = x;
    this->Y = y;
}

void RectangleShape::Update(sf::RenderWindow *window) {
    Render2D::RectDrawing(window, this);
}
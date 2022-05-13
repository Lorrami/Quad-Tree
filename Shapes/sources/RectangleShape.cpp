#include <iostream>
#include "RectangleShape.h"

RectangleShape::RectangleShape(float width, float height, float x, float y) {
    type = ShapesType::Rectangle;
    this->Width = width;
    this->Height = height;
    this->X = x;
    this->Y = y;
}

void RectangleShape::Update(sf::RenderWindow *window, DefaultShape* obj) {
    sf::CircleShape circle;
    circle.setRadius(obj->Width);
    circle.setPosition(sf::Vector2f(obj->X, obj->Y));
    circle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));

    window->draw(circle);
}
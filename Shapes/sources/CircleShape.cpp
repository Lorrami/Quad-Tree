#include <iostream>
#include "../include/CircleShape.h"

CircleShape::CircleShape(float radius, float x, float y) {
    type = ShapesType::Circle;
    this->Width = radius;
    this->Height = radius;
    this->X = x;
    this->Y = y;
}

void CircleShape::Update(sf::RenderWindow *window, DefaultShape* obj) {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(obj->Width, obj->Height));
    rect.setPosition(sf::Vector2f(obj->X, obj->Y));
    rect.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));

    window->draw(rect);
}

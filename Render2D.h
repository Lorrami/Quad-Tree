#pragma once

#include "Shapes/DefaultShape.h"
#include "Shapes/RectangleShape.h"
#include "Shapes/CircleShape.h"
#include "Application.h"

class Render2D {
public:
    static void AreaDrawing(sf::RenderWindow *window, Rectangle *area);
    static void ZoomUpdate(sf::RenderWindow *window, sf::Event event);
    static void MouseUpdate(sf::RenderWindow *window);
    static void RectDrawing(sf::RenderWindow *window, RectangleShape *obj);
    static void CircleDrawing(sf::RenderWindow *window, CircleShape *obj);
};
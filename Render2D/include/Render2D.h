#pragma once

#include "DefaultShape.h"
#include "RectangleShape.h"
#include "CircleShape.h"
#include "QuadTree.h"

class Render2D {
public:
    static void AreaDrawing(sf::RenderWindow *window, Rectangle *area);
    static void ZoomUpdate(sf::RenderWindow *window, sf::Event event);
    static void MouseUpdate(sf::RenderWindow *window);
    static void RectDrawing(sf::RenderWindow *window, RectangleShape *obj);
    static void CircleDrawing(sf::RenderWindow *window, CircleShape *obj);
};
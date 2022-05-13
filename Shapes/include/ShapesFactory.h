#pragma once

#include "RectangleShape.h"
#include "CircleShape.h"

class ShapesFactory {
public:
    static DefaultShape* CreateShape();

private:
    static int random_object();
    static float random_float(float a, float b);

    static RectangleShape* get_rect_generated();
    static CircleShape* get_circle_generated();
};
#include "ShapesFactory.h"
#include "FieldShape.h"

DefaultShape* ShapesFactory::CreateShape() {
    if(random_object() == 0) {
        return get_rect_generated();
    } else {
        return get_circle_generated();
   }
}

int ShapesFactory::random_object() {
    return rand() % 2;
}

float ShapesFactory::random_float(const float a, const float b) {
    return float(rand()) / float(RAND_MAX) * (b - a) + a;
}

RectangleShape* ShapesFactory::get_rect_generated() {
    return new RectangleShape(
            random_float(1, 10),
            random_float(1, 10),
            random_float(10, FieldShape::Width - 10),
            random_float(10, FieldShape::Height - 10));
}

CircleShape* ShapesFactory::get_circle_generated() {
    return new CircleShape(
            random_float(1, 5),
            random_float(1, FieldShape::Width - 5),
            random_float(1, FieldShape::Height - 5));
}
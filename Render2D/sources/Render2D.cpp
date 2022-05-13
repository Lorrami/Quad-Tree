#include <iostream>
#include "Render2D.h"
#include "FieldShape.h"

void Render2D::AreaDrawing(sf::RenderWindow *window, Rectangle *area) {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(area->Width, area->Height));
    rect.setOrigin(sf::Vector2f(area->Width / 2, area->Height / 2));
    rect.setPosition(sf::Vector2f(area->X, area->Y));
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(4);
    
    window->draw(rect);
}

void Render2D::ZoomUpdate(sf::RenderWindow *window, sf::Event event) {
    sf::View view = window->getView();
    if (event.mouseWheelScroll.delta > 0) {
        view.zoom(0.8f);
    }
    if (event.mouseWheelScroll.delta < 0) {
        view.zoom(1.2f);
    }
    window->setView(view);
}

void Render2D::MouseUpdate(sf::RenderWindow *window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        float dX, dY;
        sf::View view = window->getView();
        sf::Vector2f current_real_mouse_pos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        dX = current_real_mouse_pos.x - FieldShape::PreviousRealMousePosition.x;
        dY = current_real_mouse_pos.y - FieldShape::PreviousRealMousePosition.y;

        view.setCenter(sf::Vector2f(FieldShape::PreviousViewCenter.x + dX, FieldShape::PreviousViewCenter.y + dY));

        FieldShape::PreviousRealMousePosition = current_real_mouse_pos;
        FieldShape::PreviousViewCenter = view.getCenter();

        window->setView(view);
    }
}
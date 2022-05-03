#include "Render2D.h"

#include <iostream>
#include "Render2D.h"

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
        dX = current_real_mouse_pos.x - Application::Get().PreviousRealMousePosition.x;
        dY = current_real_mouse_pos.y - Application::Get().PreviousRealMousePosition.y;

        view.setCenter(sf::Vector2f(Application::Get().PreviousViewCenter.x + dX, Application::Get().PreviousViewCenter.y + dY));

        Application::Get().PreviousRealMousePosition = current_real_mouse_pos;
        Application::Get().PreviousViewCenter = view.getCenter();

        window->setView(view);
    }
}

void Render2D::RectDrawing(sf::RenderWindow *window, RectangleShape *obj) {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(obj->Width, obj->Height));
    rect.setPosition(sf::Vector2f(obj->X, obj->Y));
    rect.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
    
    window->draw(rect);
}

void Render2D::CircleDrawing(sf::RenderWindow *window, CircleShape *obj) {
    sf::CircleShape circle;
    circle.setRadius(obj->Width);
    circle.setPosition(sf::Vector2f(obj->X, obj->Y));
    circle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));

    window->draw(circle);
}
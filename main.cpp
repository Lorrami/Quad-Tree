#include "Application.h"

// int main() {

//     std::vector<Entity*> entities;
//     std::vector<Entity*> found;

//     sf::RectangleShape rect;
//     rect.setOutlineColor(sf::Color::Red);

//     int width = 5, height = 5;

//     while (window.isOpen()) {
//         quad_tree = new QuadTree(Rectangle(WIDTH / 2, HEIGHT / 2, WIDTH / 2, HEIGHT / 2), CAPACITY, 0);

//         for (auto it = entities.begin(); it != entities.end(); it++) {
//             (*it)->Move();
//             (*it)->IsCollided = false;
//             quad_tree->Insert(*it);
//         }

//         quad_tree->CheckCollision();

//         rect.setOutlineThickness(0);
//         rect.setPosition(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
//         rect.setSize(sf::Vector2f(width * 2, height * 2));
//         rect.setOrigin(sf::Vector2f(width, height));
//         rect.setFillColor(sf::Color(255, 255, 0, 50));
//         window.draw(rect);


//         window.display();
//     }
//     for (auto i = 0; i < entities.size(); i++) {
//         delete entities[i];
//     }
//     delete quad_tree;
//     return 777;
// }

int main() {
    Application::Get().Run();
    return 777;
}
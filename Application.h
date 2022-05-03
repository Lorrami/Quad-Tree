#pragma once

#include <SFML/Graphics.hpp>
#include "Shapes/Defaultshape.h"
#include "Shapes/ShapesFactory.h"
#include "QuadTree.h"

class Application {
public:
    static Application *s_Instance;
    sf::RenderWindow Window{sf::VideoMode(1280, 720), "Quad Tree"};
    sf::Vector2f PreviousRealMousePosition;
    sf::Vector2f PreviousViewCenter;
    int Width, Height;
private:
    sf::Clock m_Clock;
    sf::Font m_Font;
    int m_Count;
    int m_Capacity = 2;

    std::vector<DefaultShape*> m_Objects{};
    QuadTree *m_QuadTree;

    void GetCount();
    void CreateWindow();
    void GenerateField();
    void CreateQuadTree();
    void HandleEvents();
    void Draw();
public:
    void Run();

    static Application &Get();
};
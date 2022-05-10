#pragma once

#include <SFML/Graphics.hpp>
#include "Shapes/Defaultshape.h"
#include "Shapes/ShapesFactory.h"
#include "QuadTree.h"

#include <mutex>
#include <thread>

struct DataBuffer {
    static std::vector<DefaultShape*> DrawableObjects;
};

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
    size_t m_Count{};
    float m_Scale = 1.0f;
    float m_DeltaTime{};
    int m_Capacity = 2;
    bool m_IsQuadTreeDrawable = true;
    bool m_IsRunning = true;

    std::vector<DefaultShape*> m_Objects{};
    std::vector<DefaultShape*> m_VisibleObjects{};
    std::mutex m_Mutex;
    QuadTree *m_QuadTree;
    Rectangle m_Area{800.f, 600.f, 640.f, 360.f};

    void GetCount();
    void CreateWindow();
    void GenerateField();
    void CreateQuadTree();
    void HandleEvents();
    void CheckCount();
    void DrawCount();
    void DrawTime();
    void UpdatingThreadFunc();
    void DrawingThreadFunc();
public:
    void Run();

    static Application &Get();
};
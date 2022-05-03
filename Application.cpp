#include "Application.h"
#include "Render2D.h"

#include <iostream>

Application *Application::s_Instance = nullptr;

void Application::GetCount() {
    std::cout << "Enter objects count:";
    std::cin >> m_Count;
}

void Application::CreateWindow() {
    std::cout << "Enter width:";
    std::cin >> Width;
    std::cout << "Enter height:";
    std::cin >> Height;
    m_Font.loadFromFile("../../Materials/Text1.ttf");
}

void Application::GenerateField() {
    int i = 0;
    while(i < m_Count) {
        i++;
        m_Objects.push_back(ShapesFactory::CreateShape());
    }
}

void Application::CreateQuadTree() {
    m_QuadTree = new QuadTree(Rectangle(Width / 2, Height / 2, Width / 2, Height / 2), m_Capacity, 0);

    for (auto it = m_Objects.begin(); it != m_Objects.end(); it++) {
        m_QuadTree->Insert(*it);
    }
}

void Application::HandleEvents() {
    sf::Event event;
    while (Window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            Window.close();
            break;
        }    
        if (sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left) {
            PreviousRealMousePosition = Window.mapPixelToCoords(sf::Mouse::getPosition(Window));
            PreviousViewCenter = Window.getView().getCenter();
        }
        if (event.type == sf::Event::MouseWheelScrolled)
            Render2D::ZoomUpdate(&Window, event);
    }
}

void Application::DrawTime() {
    sf::Text *m_TimeText = new sf::Text(std::to_string(m_DeltaTime), m_Font, 30);
    m_TimeText->setFillColor(sf::Color::White);
    m_TimeText->setPosition(Window.getView().getCenter() + sf::Vector2f(480.0f, -360.f));
    Window.draw(*m_TimeText);
}

void Application::Draw() {
    while(Window.isOpen()) {
        HandleEvents();
        m_DeltaTime = m_Clock.getElapsedTime().asSeconds();
        m_Clock.restart();
        Window.clear();
        Render2D::MouseUpdate(&Window);
        for (auto obj : m_Objects) {
            obj->Update(&Window);
        }
        m_QuadTree->Draw(Window);
        DrawTime();
        Window.display();
    }
}

void Application::Run() {
    GetCount();
    CreateWindow();
    GenerateField();
    CreateQuadTree();
    Draw();
}

Application &Application::Get() {
    if(s_Instance == nullptr) {
        s_Instance = new Application();
    }
    return *s_Instance;
}
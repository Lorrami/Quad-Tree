#include "../include/Application.h"
#include "Render2D.h"
#include "FieldShape.h"

#include <iostream>

Application *Application::s_Instance = nullptr;
std::vector<DefaultShape*> DataBuffer::DrawableObjects{};

void Application::GetCount() {
    std::cout << "Enter objects count:";
    std::cin >> m_Count;
}

void Application::CreateWindow() {
    std::cout << "Enter width:";
    std::cin >> FieldShape::Width;
    std::cout << "Enter height:";
    std::cin >> FieldShape::Height;
    if (!m_Font.loadFromFile("Materials/Text1.ttf"))
        std::cout << "FAILD TO LOAD TEXT FACE\n";
}

void Application::GenerateField() {
    int i = 0;
    while(i < m_Count) {
        i++;
        m_Objects.push_back(ShapesFactory::CreateShape());
    }
}

void Application::CreateQuadTree() {
    if(FieldShape::Height != FieldShape::Width) {
        if (FieldShape::Height > FieldShape::Width) {
            m_QuadTree = new QuadTree(Rectangle(FieldShape::Height / 2, FieldShape::Height / 2, 
                                                FieldShape::Height / 2, FieldShape::Height / 2), m_Capacity, 0);
        } else
        if (FieldShape::Width > FieldShape::Height)
            m_QuadTree = new QuadTree(Rectangle(FieldShape::Width / 2, FieldShape::Width / 2,
                                                FieldShape::Width / 2, FieldShape::Width / 2), m_Capacity, 0);
    } else 
        m_QuadTree = new QuadTree(Rectangle(FieldShape::Width / 2, FieldShape::Height / 2,
                                            FieldShape::Width / 2, FieldShape::Height / 2), m_Capacity, 0);

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
            FieldShape::PreviousRealMousePosition = Window.mapPixelToCoords(sf::Mouse::getPosition(Window));
            FieldShape::PreviousViewCenter = Window.getView().getCenter();
        }
        if (event.type == sf::Event::MouseWheelScrolled)
            Render2D::ZoomUpdate(&Window, event);
        if (sf::Event::MouseButtonPressed && event.key.code == sf::Keyboard::LControl) {
            m_IsQuadTreeDrawable = true;
        } 
        if (sf::Event::MouseButtonPressed && event.key.code == sf::Keyboard::LAlt) {
            m_IsQuadTreeDrawable = false;
        } 
    }
}

void Application::CheckCount() {
    m_DeltaTime = m_Clock.getElapsedTime().asSeconds();
    m_Clock.restart();
    sf::View view = Window.getView();
    m_QuadTree->Find(Rectangle(view.getCenter().x, view.getCenter().y,
                                view.getSize().x, view.getSize().y), m_VisibleObjects);
}

void Application::DrawCount() {
    sf::Text count_text = sf::Text("Objects in view: " + std::to_string(DataBuffer::DrawableObjects.size()), m_Font, 30);
    count_text.setFillColor(sf::Color::White);
    count_text.setScale(sf::Vector2f(m_Scale, m_Scale));
    count_text.setPosition(Window.getView().getCenter() + sf::Vector2f(-500.f * m_Scale, -290.f * m_Scale));
    Window.draw(count_text);
}

void Application::DrawTime() {
    sf::Text time_text = sf::Text("Time to search: " + std::to_string(m_DeltaTime), m_Font, 30);
    time_text.setFillColor(sf::Color::White);
    time_text.setScale(sf::Vector2f(m_Scale, m_Scale));
    time_text.setPosition(Window.getView().getCenter() + sf::Vector2f(180.f * m_Scale, -290.f * m_Scale));
    Window.draw(time_text);
}

void Application::UpdatingThreadFunc() {
    while (m_IsRunning) {
        CheckCount();
        m_QuadTree->Reset();
        m_Mutex.lock();
        DataBuffer::DrawableObjects = m_VisibleObjects;
        m_VisibleObjects.clear();
        m_Mutex.unlock();
    }
}

void Application::DrawingThreadFunc() {
    while(Window.isOpen()) {
        HandleEvents();
        Render2D::MouseUpdate(&Window);
        m_Scale = Window.getView().getSize().x / 1000.f;

        Window.clear();
        m_Mutex.lock();
        for (auto obj : DataBuffer::DrawableObjects) {
            obj->Update(&Window, obj);
        }
        if (m_IsQuadTreeDrawable) 
            m_QuadTree->Draw(Window);
        m_Mutex.unlock();

        DrawTime();
        DrawCount();
        Window.display();
    }
    m_IsRunning = false;
}

void Application::Run() {
    GetCount();
    CreateWindow();
    GenerateField();
    CreateQuadTree();
    
    std::thread updating_thread([this]{
        UpdatingThreadFunc();
    });
    DrawingThreadFunc();
    updating_thread.join();
}

Application &Application::Get() {
    if(s_Instance == nullptr) {
        s_Instance = new Application();
    }
    return *s_Instance;
}
#pragma once

#include "SFML/Graphics.hpp"
#include "Shapes/Defaultshape.h"

struct Rectangle {
    float X, Y;
    float Height, Width;
    Rectangle(float x, float y, float height, float width) : X(x), Y(y), Height(height), Width(width) {}

    bool Intersects(const Rectangle& other) const;

    void Draw(sf::RenderTarget& target);
};

struct QuadTree {
private:
    QuadTree* m_TopLeft;
    QuadTree* m_TopRight;
    QuadTree* m_BottomLeft;
    QuadTree* m_BottomRight;
    Rectangle m_Bounds;

    size_t m_Capacity;
    size_t m_Level;
    bool m_IsDivided;

    int m_MaxLevel = 7;

    std::vector<DefaultShape*> m_Children;

    void SubDivide();
public:
    QuadTree(const Rectangle& bounds, size_t capacity, size_t level) :
            m_TopLeft(nullptr), m_TopRight(nullptr), m_BottomLeft(nullptr), m_BottomRight(nullptr), m_IsDivided(false),
            m_Bounds(bounds), m_Capacity(capacity), m_Level(level) {
        if (level >= m_MaxLevel) {
            m_Capacity = 0;
        }
    }
    ~QuadTree();

    void Insert(DefaultShape *shape);

    void Find(const Rectangle& area, std::vector<DefaultShape*>& found) const;

    void Draw(sf::RenderTarget& target);
};

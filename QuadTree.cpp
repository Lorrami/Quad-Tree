#include "QuadTree.h"
#include "Application.h"
#include <iostream>

bool Rectangle::Intersects(const Rectangle& other) const {
    return !(X - Width > other.X + other.Width ||
            X + Width < other.X - other.Width ||
            Y - Height > other.Y + other.Height ||
            Y + Height < other.Y - other.Height);
}

void Rectangle::Draw(sf::RenderTarget& target) {
    static sf::Vertex verteces[5];
    verteces[0] = sf::Vertex(sf::Vector2f(X, Y), sf::Color::Magenta);
    verteces[1] = sf::Vertex(sf::Vector2f(X + Width, Y - Height), sf::Color::Magenta);
    verteces[2] = sf::Vertex(sf::Vector2f(X + Width, Y + Height), sf::Color::Magenta);
    verteces[3] = sf::Vertex(sf::Vector2f(X - Width, Y + Height), sf::Color::Magenta);
    verteces[4] = sf::Vertex(sf::Vector2f(X, Y), sf::Color::Magenta);
    target.draw(verteces, 5, sf::LineStrip);
    std::cout << "RECT: " << X << " " << Y << '\n' <<
                            X + Width << " " << Y - Height << '\n' <<
                            X + Width << " " << Y + Height << '\n' <<
                            X - Width << " " << Y + Height << '\n' <<
                            X << " " << Y << '\n';
    std::cout << '\n';
    sf::View view = target.getView();
    std::cout << "VIEW: " << view.getCenter().x << " " << view.getCenter().y << " " << view.getSize().x << " " << view.getSize().y << '\n';
}

void QuadTree::SubDivide() {
    sf::Vector2f half_size = sf::Vector2f(m_Bounds.Width / 2.f, m_Bounds.Height / 2.f);
    m_TopLeft = new QuadTree(Rectangle(m_Bounds.X - half_size.x, m_Bounds.Y - half_size.y, half_size.x, half_size.y),
                         m_Capacity, m_Level + 1);
    m_TopRight = new QuadTree(Rectangle(m_Bounds.X + half_size.x, m_Bounds.Y - half_size.y, half_size.x, half_size.y),
                          m_Capacity, m_Level + 1);
    m_BottomLeft = new QuadTree(Rectangle(m_Bounds.X - half_size.x, m_Bounds.Y + half_size.y, half_size.x, half_size.y),
                            m_Capacity, m_Level + 1);
    m_BottomRight = new QuadTree(Rectangle(m_Bounds.X + half_size.x, m_Bounds.Y + half_size.y, half_size.x, half_size.y),
                             m_Capacity, m_Level + 1);
    m_IsDivided = true;
}

QuadTree::~QuadTree() {
    if (m_IsDivided) {
        delete m_TopLeft;
        delete m_TopRight;
        delete m_BottomLeft;
        delete m_BottomRight;
    }
}

void QuadTree::Insert(DefaultShape *shape) {
    if (!m_Bounds.Intersects(Rectangle(shape->X, shape->Y, shape->Width, shape->Height))) {
		return;
	}
    if (!m_IsDivided) {
        m_Children.push_back(shape);
        if (m_Children.size() > m_Capacity && m_Capacity != 0) {
            SubDivide();
            std::vector<DefaultShape*>::iterator it = m_Children.begin();
            while (it != m_Children.end()) {
                m_TopLeft->Insert(*it);
                m_TopRight->Insert(*it);
                m_BottomLeft->Insert(*it);
                m_BottomRight->Insert(*it);
                it = m_Children.erase(it);
            }
        }
    } else {
        m_TopLeft->Insert(shape);
        m_TopRight->Insert(shape);
        m_BottomLeft->Insert(shape);
        m_BottomRight->Insert(shape);
    }
}

void QuadTree::Find(const Rectangle& area, std::vector<DefaultShape*>& found) const {
    if (!area.Intersects(m_Bounds)) {
        return;
    }
    if (m_IsDivided) {
        m_TopLeft->Find(area, found);
        m_TopRight->Find(area, found);
        m_BottomLeft->Find(area, found);
        m_BottomRight->Find(area, found);
    } else {
        for (auto i = 0; i < m_Children.size(); i++) {
            if (!m_Children[i]->IsCheckedByTree) {
                if (m_Children[i]->X <= area.X + area.Width / 2 - m_Children[i]->Width &&
                    m_Children[i]->X >= area.X - area.Width / 2 &&
                    m_Children[i]->Y <= area.Y + area.Height / 2 - m_Children[i]->Height &&
                    m_Children[i]->Y >= area.Y - area.Height / 2) {
                    found.push_back(m_Children[i]);
                    m_Children[i]->IsCheckedByTree = true;
                }
            }
        }
    }
}

void QuadTree::Reset() {
    if (m_IsDivided) {
        m_TopLeft->Reset();
        m_TopRight->Reset();
        m_BottomLeft->Reset();
        m_BottomRight->Reset();
    } else {
        for (auto i = 0; i < m_Children.size(); i++) {
            m_Children[i]->IsCheckedByTree = false;
        }
    }
}

void QuadTree::Draw(sf::RenderTarget& target) {
    if (m_IsDivided) {
        sf::Vertex verteces[4];
        verteces[0] = sf::Vertex(sf::Vector2f(m_Bounds.X, m_Bounds.Y - m_Bounds.Height), sf::Color::White);
        verteces[1] = sf::Vertex(sf::Vector2f(m_Bounds.X, m_Bounds.Y + m_Bounds.Height), sf::Color::White);
        verteces[2] = sf::Vertex(sf::Vector2f(m_Bounds.X - m_Bounds.Width, m_Bounds.Y), sf::Color::White);
        verteces[3] = sf::Vertex(sf::Vector2f(m_Bounds.X + m_Bounds.Width, m_Bounds.Y), sf::Color::White);
        target.draw(verteces, 4, sf::Lines);
        m_TopLeft->Draw(target);
        m_TopRight->Draw(target);
        m_BottomLeft->Draw(target);
        m_BottomRight->Draw(target);
    }
}
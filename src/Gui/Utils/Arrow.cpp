/*
 * This file is part of sfml3-widgets (https://github.com/dualword/sfml3-widgets)
 * License: MIT
 */

#include "Arrow.hpp"
#include "../Theme.hpp"

namespace gui
{

Arrow::Arrow(Direction direction): m_direction(direction)
{
    const sf::IntRect& rect = Theme::getArrowTextureRect();

    m_vertices[0].texCoords = sf::Vector2f(rect.position.x, rect.position.y);
    m_vertices[1].texCoords = sf::Vector2f(rect.position.x + rect.size.x, rect.position.y);
    m_vertices[2].texCoords = sf::Vector2f(rect.position.x + rect.size.x, rect.position.y + rect.size.y);
    m_vertices[3].texCoords = sf::Vector2f(rect.position.x + rect.size.x, rect.position.y + rect.size.y);
    m_vertices[4].texCoords = sf::Vector2f(rect.position.x, rect.position.y + rect.size.y);
    m_vertices[5].texCoords = sf::Vector2f(rect.position.x, rect.position.y);

    updateGeometry(0, 0, direction);
}

void Arrow::setFillColor(const sf::Color& color)
{
    for (int i = 0; i < 6; ++i)
        m_vertices[i].color = color;
}

void Arrow::setPosition(float x, float y)
{
    updateGeometry(x, y, m_direction);
}

void Arrow::move(float dx, float dy)
{
    for (int i = 0; i < 6; ++i)
    {
        m_vertices[i].position.x += dx;
        m_vertices[i].position.y += dy;
    }
}

void Arrow::move(sf::Vector2f offset)
{
    move(offset.x, offset.y);
}

sf::Vector2f Arrow::getSize() const
{
    const sf::IntRect& rect = Theme::getArrowTextureRect();
    return sf::Vector2f(rect.size.x, rect.size.y);
}

void Arrow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.texture = &Theme::getTexture();
    target.draw(m_vertices, 6, sf::PrimitiveType::Triangles, states);
}

void Arrow::updateGeometry(float x, float y, Direction direction)
{
    const sf::IntRect& rect = Theme::getArrowTextureRect();
    const float sx = static_cast<float>(rect.size.x);
    const float sy = static_cast<float>(rect.size.y);

    sf::Vector2f p0, p1, p2, p3;
    switch (direction)
    {
    case Top:
        p0 = sf::Vector2f(x, y);
        p1 = sf::Vector2f(x + sx, y);
        p2 = sf::Vector2f(x + sx, y + sy);
        p3 = sf::Vector2f(x, y + sy);
        break;
    case Bottom:
        p0 = sf::Vector2f(x + sx, y + sy);
        p1 = sf::Vector2f(x, y + sy);
        p2 = sf::Vector2f(x, y);
        p3 = sf::Vector2f(x + sx, y);
        break;
    case Left:
        p0 = sf::Vector2f(x, y + sx);
        p1 = sf::Vector2f(x, y);
        p2 = sf::Vector2f(x + sy, y);
        p3 = sf::Vector2f(x + sy, y + sx);
        break;
    case Right:
        p0 = sf::Vector2f(x + sy, y);
        p1 = sf::Vector2f(x + sy, y + sx);
        p2 = sf::Vector2f(x, y + sx);
        p3 = sf::Vector2f(x, y);
        break;
    }

    m_vertices[0].position = p0;
    m_vertices[1].position = p1;
    m_vertices[2].position = p2;
    m_vertices[3].position = p2;
    m_vertices[4].position = p3;
    m_vertices[5].position = p0;

    m_direction = direction;
}

}

/*
 * This file is part of sfml3-widgets (https://github.com/dualword/sfml3-widgets)
 * License: MIT
 */

#include "Cross.hpp"
#include "../Theme.hpp"

namespace gui
{

Cross::Cross()
{
    const sf::IntRect& rect = Theme::getCrossTextureRect();

    m_vertices[0].texCoords = sf::Vector2f(rect.position.x, rect.position.y);
    m_vertices[1].texCoords = sf::Vector2f(rect.position.x + rect.size.x, rect.position.y);
    m_vertices[2].texCoords = sf::Vector2f(rect.position.x + rect.size.x, rect.position.y + rect.size.y);
    m_vertices[3].texCoords = sf::Vector2f(rect.position.x + rect.size.x, rect.position.y + rect.size.y);
    m_vertices[4].texCoords = sf::Vector2f(rect.position.x, rect.position.y + rect.size.y);
    m_vertices[5].texCoords = sf::Vector2f(rect.position.x, rect.position.y);

    updateGeometry(0, 0);
}

void Cross::setPosition(float x, float y)
{
    updateGeometry(x, y);
}

void Cross::move(float dx, float dy)
{
    for (int i = 0; i < 6; ++i)
    {
        m_vertices[i].position.x += dx;
        m_vertices[i].position.y += dy;
    }
}

void Cross::setSize(float) { }

sf::Vector2f Cross::getSize() const
{
    const sf::IntRect& rect = Theme::getCrossTextureRect();
    return sf::Vector2f(static_cast<float>(rect.size.x), static_cast<float>(rect.size.y));
}

void Cross::setColor(const sf::Color& color)
{
    for (int i = 0; i < 6; ++i)
        m_vertices[i].color = color;
}

void Cross::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.texture = &Theme::getTexture();
    target.draw(m_vertices, 6, sf::PrimitiveType::Triangles, states);
}

void Cross::updateGeometry(float x, float y)
{
    const sf::IntRect& rect = Theme::getCrossTextureRect();
    const float sx = static_cast<float>(rect.size.x);
    const float sy = static_cast<float>(rect.size.y);

    sf::Vector2f p0(x, y);
    sf::Vector2f p1(x + sx, y);
    sf::Vector2f p2(x + sx, y + sy);
    sf::Vector2f p3(x, y + sy);

    m_vertices[0].position = p0;
    m_vertices[1].position = p1;
    m_vertices[2].position = p2;

    m_vertices[3].position = p2;
    m_vertices[4].position = p3;
    m_vertices[5].position = p0;
}

}

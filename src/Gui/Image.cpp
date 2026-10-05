/*
 * This file is part of sfml3-widgets (https://github.com/dualword/sfml3-widgets)
 * License: MIT
 */

#include "Image.hpp"

namespace gui
{

Image::Image(): m_texture(nullptr)
{
    setSelectable(false);
}

Image::Image(const sf::Texture& texture):
    m_texture(nullptr)
{
    setSelectable(false);
    setTexture(texture);
}

void Image::setTexture(const sf::Texture& texture)
{
    int width = texture.getSize().x;
    int height = texture.getSize().y;

    sf::Vector2f topLeft(0.f, 0.f);
    sf::Vector2f bottomLeft(0.f, height);
    sf::Vector2f bottomRight(width, height);
    sf::Vector2f topRight(width, 0.f);

    m_vertices[0].position = m_vertices[0].texCoords = topLeft;
    m_vertices[1].position = m_vertices[1].texCoords = bottomLeft;
    m_vertices[2].position = m_vertices[2].texCoords = bottomRight;
    m_vertices[3].position = m_vertices[3].texCoords = topLeft;
    m_vertices[4].position = m_vertices[4].texCoords = bottomRight;
    m_vertices[5].position = m_vertices[5].texCoords = topRight;

    m_texture = &texture;
    setSize(width, height);
}

void Image::setColor(const sf::Color& color)
{
    for (int i = 0; i < 6; ++i)
        m_vertices[i].color = color;
}

void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_texture != nullptr)
    {
        states.transform *= getTransform();
        states.texture = m_texture;
        target.draw(m_vertices, 6, sf::PrimitiveType::Triangles, states);

    }
}

}

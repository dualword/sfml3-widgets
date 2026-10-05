/*
 * This file is part of sfml3-widgets (https://github.com/dualword/sfml3-widgets)
 * License: MIT
 */

#ifndef GUI_ARROW_HPP
#define GUI_ARROW_HPP

#include <SFML/Graphics.hpp>

namespace gui
{

class Arrow: public sf::Drawable
{
public:
    enum Direction
    {
        Left,
        Right,
        Top,
        Bottom
    };

    Arrow(Direction direction);

    void setFillColor(const sf::Color& color);

    void move(float dx, float dy);
    void move(sf::Vector2f offset);
    void setPosition(float x, float y);

    sf::Vector2f getSize() const;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void updateGeometry(float x, float y, Direction direction);

    sf::Vertex m_vertices[6];
    Direction m_direction;
};

}

#endif // GUI_ARROW_HPP

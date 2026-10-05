/*
 * This file is part of sfml3-widgets (https://github.com/dualword/sfml3-widgets)
 * License: MIT
 */

#include "Menu.hpp"
#include "Theme.hpp"

namespace gui
{

Menu::Menu(sf::RenderWindow& window):
    m_window(window),
    m_cursorType(sf::Cursor::Type::Arrow)
{
}

void Menu::onEvent(const sf::Event& event)
{
    if (const auto* mouseMoved = event.getIf<sf::Event::MouseMoved>())
    {
        sf::Vector2f mouse = convertMousePosition(mouseMoved->position.x, mouseMoved->position.y);
        onMouseMoved(mouse.x, mouse.y);
    }
    else if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mousePressed->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f mouse = convertMousePosition(mousePressed->position.x, mousePressed->position.y);
            onMousePressed(mouse.x, mouse.y);
        }
    }
    else if (const auto* mouseReleased = event.getIf<sf::Event::MouseButtonReleased>())
    {
        if (mouseReleased->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f mouse = convertMousePosition(mouseReleased->position.x, mouseReleased->position.y);
            onMouseReleased(mouse.x, mouse.y);
        }
    }
    else if (const auto* mouseWheel = event.getIf<sf::Event::MouseWheelScrolled>())
    {
        onMouseWheelMoved(mouseWheel->delta);
    }
    else if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        onKeyPressed(*keyPressed);
    }
    else if (const auto* textEntered = event.getIf<sf::Event::TextEntered>())
    {
        onTextEntered(textEntered->unicode);
    }
}

sf::Vector2f Menu::convertMousePosition(int x, int y) const
{
    sf::Vector2f mouse = m_window.mapPixelToCoords(sf::Vector2i(x, y));
    mouse -= getPosition();
    return mouse;
}

void Menu::setMouseCursor(sf::Cursor::Type cursorType)
{
    if (cursorType != m_cursorType)
    {
        gui::Theme::cursor.createFromSystem(cursorType);
        m_window.setMouseCursor(gui::Theme::cursor);
        m_cursorType = cursorType;
    }
}

}

/*
 * This file is part of sfml3-widgets (https://github.com/dualword/sfml3-widgets)
 * License: MIT
 */

#include "SpriteButton.hpp"
#include "Theme.hpp"

namespace gui
{

SpriteButton::SpriteButton(const sf::Texture& texture, const sf::String& string):
    Widget(),
    m_background(texture),
    m_pressed(false)
{
    size_t width = texture.getSize().x;
    size_t height = texture.getSize().y / 3; // default, hover, focus

    m_background.setTexture(texture);
    m_background.setTextureRect(sf::IntRect({0, 0}, {static_cast<int>(width), static_cast<int>(height)}));

    setSize(width, height);

    m_text.setFont(Theme::getFont());
    m_text.setCharacterSize(Theme::textSize);

    setString(string);
}


void SpriteButton::setString(const sf::String& string)
{
    m_text.setString(string);
    centerText(m_text);
}


const sf::String& SpriteButton::getString() const
{
    return m_text.getString();
}


void SpriteButton::setFont(const sf::Font& font)
{
    m_text.setFont(font);
    centerText(m_text);
}


const sf::Font& SpriteButton::getFont() const
{
    return m_text.getFont();
}


void SpriteButton::setTextSize(size_t size)
{
    m_text.setCharacterSize(size);
    centerText(m_text);
}


void SpriteButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_background, states);
    target.draw(m_text, states);
}


// Callbacks -------------------------------------------------------------------

void SpriteButton::onStateChanged(State state)
{
    sf::Vector2f size = getSize();
    switch (state)
    {
    case StateDefault:
        m_background.setTextureRect(sf::IntRect({0, 0}, {static_cast<int>(size.x), static_cast<int>(size.y)}));
        break;
    case StateHovered:
        m_background.setTextureRect(sf::IntRect({0, static_cast<int>(size.y)}, {static_cast<int>(size.x), static_cast<int>(size.y)}));
        break;
    case StatePressed:
    case StateFocused:
        m_background.setTextureRect(sf::IntRect({0, static_cast<int>(size.y * 2)}, {static_cast<int>(size.x), static_cast<int>(size.y)}));
        break;
    }
}


void SpriteButton::onMouseMoved(float x, float y)
{
    if (isFocused())
    {
        if (containsPoint({x, y}) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            press();
        else
            release();
    }
}


void SpriteButton::onMousePressed(float, float)
{
    press();
}


void SpriteButton::onMouseReleased(float x, float y)
{

    release();
    if (containsPoint({x, y}))
    {
        triggerCallback();
    }
}


void SpriteButton::onKeyPressed(const sf::Event::KeyPressed& key)
{
    if (key.code == sf::Keyboard::Key::Enter)
    {
        triggerCallback();
        press();
    }
}


void SpriteButton::onKeyReleased(const sf::Event::KeyPressed& key)
{
    if (key.code == sf::Keyboard::Key::Enter)
        release();
}


void SpriteButton::press()
{
    if (!m_pressed)
    {
        m_pressed = true;
        m_text.move({0, 1});
    }
}


void SpriteButton::release()
{
    if (m_pressed)
    {
        m_pressed = false;
        m_text.move({0, -1});
    }
}

}

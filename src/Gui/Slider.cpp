/*
 * This file is part of sfml3-widgets (https://github.com/dualword/sfml3-widgets)
 * License: MIT
 */

#include "Slider.hpp"
#include "Theme.hpp"

namespace gui
{

Slider::Slider(float length, Orientation orientation):
    m_orientation(orientation),
    m_step(10),
    m_value(0),
    m_box(Box::Input)
{
    float handleHeight = Theme::getBoxHeight();
    float handleWidth = handleHeight / 2.f;
    float boxHeight = Theme::borderSize * 3;
    float boxOffset = (handleHeight - boxHeight) / 2.f;

    if (orientation == Horizontal)
    {
        m_box.setSize(length, boxHeight);
        m_box.setPosition(0.f, boxOffset);
        m_handle.setSize(handleWidth, handleHeight);
        setSize(length, handleHeight);
        float x1 = m_box.getPosition().x + Theme::borderSize;
        float y1 = m_box.getPosition().y + Theme::borderSize;
        float x2 = x1;
        float y2 = y1 + m_box.getSize().y - Theme::borderSize * 2;

        sf::Vector2f topLeft(x1, y1);
        sf::Vector2f topRight(x2, y1);
        sf::Vector2f bottomRight(x2, y2);
        sf::Vector2f bottomLeft(x1, y2);

        m_progression[0].position = topLeft;
        m_progression[1].position = topRight;
        m_progression[2].position = bottomRight;
        m_progression[3].position = topLeft;
        m_progression[4].position = bottomRight;
        m_progression[5].position = bottomLeft;
    }
    else
    {
        m_box.setSize(boxHeight, length);
        m_box.setPosition(boxOffset, 0.f);
        m_handle.setSize(handleHeight, handleWidth);

        setSize(handleHeight, length);
        float x1 = m_box.getPosition().x + Theme::borderSize;
        float y1 = m_box.getPosition().y + Theme::borderSize;
        float x2 = x1 + m_box.getSize().x - Theme::borderSize * 2;
        float y2 = m_box.getSize().y - Theme::borderSize;

        sf::Vector2f topLeft(x1, y1);
        sf::Vector2f topRight(x2, y1);
        sf::Vector2f bottomRight(x2, y2);
        sf::Vector2f bottomLeft(x1, y2);
        m_progression[0].position = topLeft;
        m_progression[1].position = topRight;
        m_progression[2].position = bottomRight;
        m_progression[3].position = topLeft;
        m_progression[4].position = bottomRight;
        m_progression[5].position = bottomLeft;
    }

    for (int i = 0; i < 6; ++i)
    {
        m_progression[i].color = Theme::windowBgColor;
    }

    updateHandlePosition();
}

int Slider::getStep() const
{
    return m_step;
}

void Slider::setStep(int step)
{
    if (step > 0 && step < 100)
        m_step = step;
}

int Slider::getValue() const
{
    return m_value;
}

void Slider::setValue(int value)
{
    if (value < 0)
        value = 0;
    else if (value > 100)
        value = 100;
    else
    {
        int temp = value + m_step / 2;
        value = temp - temp % m_step;
    }

    if (value != m_value)
    {
        m_value = value;
        triggerCallback();
        updateHandlePosition();
    }
}

void Slider::updateHandlePosition()
{
    if (m_orientation == Horizontal)
    {
        float max = getSize().x - m_handle.getSize().x - Theme::borderSize * 2;
        float x = max * m_value / 100.f + Theme::borderSize;
        m_handle.setPosition(x, 0.f);
        m_progression[1].position.x = x;
        m_progression[2].position.x = x;
        m_progression[4].position.x = x;
    }
    else
    {
        float max = getSize().y - m_handle.getSize().y - Theme::borderSize * 2;
        float reverse_value = 100.f - m_value;
        float y = max * reverse_value / 100.f + Theme::borderSize;
        m_handle.setPosition(0.f, y);
        m_progression[0].position.y = y;
        m_progression[3].position.y = y;
        m_progression[5].position.y = y;
    }
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_box, states);
    target.draw(m_progression, 6, sf::PrimitiveType::Triangles, states);
    target.draw(m_handle, states);
}

// callbacks ------------------------------------------------------------------

void Slider::onKeyPressed(const sf::Event::KeyPressed& key)
{
    switch (key.code)
    {
    case sf::Keyboard::Key::Left:
        setValue(m_value - m_step);
        break;
    case sf::Keyboard::Key::Right:
        setValue(m_value + m_step);
        break;
    case sf::Keyboard::Key::Home:
        setValue(0);
        break;
    case sf::Keyboard::Key::End:
        setValue(100);
        break;
    default:
        break;
    }
}

void Slider::onMousePressed(float x, float y)
{
    if (m_orientation == Horizontal)
        setValue(100 * x / getSize().x);
    else
        setValue(100 - (100 * (y) / getSize().y));

    m_handle.press();
}

void Slider::onMouseMoved(float x, float y)
{
    if (getState() == StateFocused)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            if (m_orientation == Horizontal)
                setValue(100 * x / getSize().x);
            else
                setValue(100 - (100 * y / getSize().y));
        }
    }
    else if (m_handle.containsPoint(x, y))
    {
        m_handle.applyState(StateHovered);
    }
    else
    {
        m_handle.applyState(StateDefault);
    }
}

void Slider::onMouseReleased(float, float)
{
    m_handle.release();
}

void Slider::onMouseWheelMoved(int delta)
{
    setValue(m_value + (delta > 0 ? m_step : -m_step));
}

void Slider::onStateChanged(State state)
{
    if (state == StateFocused || state == StateDefault)
    {
        m_handle.applyState(state);
    }
}

}

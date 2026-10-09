/*
 * This file is part of sfml3-widgets (https://github.com/dualword/sfml3-widgets)
 * License: MIT
 */

#include "RadioButton.hpp"
#include <Gui/Theme.hpp>

namespace gui
{

RadioButton::RadioButton(const sf::String& label, bool checked)
    : m_checked(checked),  m_text(Theme::getFont())
{
    m_text.setFont(Theme::getFont());
    m_text.setCharacterSize(Theme::textSize);
    m_text.setFillColor(Theme::input.textColor);
    m_text.setString(label);

    float radius = Theme::getBoxHeight() * 0.6 / 2.f;
    m_circle.setRadius(radius);
    m_circle.setOutlineThickness(1);
    m_circle.setPointCount(80);

    m_indicator.setRadius(radius * 0.5f);
    m_indicator.setPointCount(80);
    m_indicator.setRadius(radius * 0.5f);

    onStateChanged(StateDefault);
    updateGeometry();
}

void RadioButton::setChecked(bool checked)
{
    m_checked = checked;
    if (m_checked) {
        if (getState() == StateHovered || getState() == StateFocused) {
            m_indicator.setFillColor(Theme::click.textColor);
        } else {
            m_indicator.setFillColor(Theme::input.textColor);
        }
    }
}

bool RadioButton::isChecked() const
{
    return m_checked;
}

void RadioButton::updateGeometry()
{
    float totalHeight = Theme::getBoxHeight();
    float circleDiameter = m_circle.getRadius() * 2.f;

    float circleYOffset = std::floor((totalHeight - circleDiameter) / 2.f);
    m_circle.setPosition({0, circleYOffset});

    float centerOffset = (circleDiameter - (m_indicator.getRadius() * 2.f)) / 2.f;
    m_indicator.setPosition({centerOffset, circleYOffset + centerOffset});

    float textYOffset = std::floor((totalHeight - m_text.getLocalBounds().size.y) / 2.f);
    m_text.setPosition({circleDiameter + Theme::PADDING + 1, circleYOffset});
    setSize(circleDiameter + Theme::PADDING + m_text.getLocalBounds().size.y, totalHeight);
}

void RadioButton::onStateChanged(State state)
{
    if (state == StateHovered || state == StateFocused) {
        sf::Color hoverGray(170, 170, 170);
        m_circle.setFillColor(Theme::windowBgColor);
        m_circle.setOutlineColor(hoverGray);
        m_text.setFillColor(hoverGray);
    }
    else {
        m_circle.setFillColor(Theme::windowBgColor);
        m_circle.setOutlineColor(Theme::input.textColor);
        m_indicator.setFillColor(Theme::input.textColor);
        m_text.setFillColor(Theme::input.textColor);
    }
}

bool RadioButton::isHighlighted(float x, float y) const
{
    float totalHeight = Theme::getBoxHeight();
    float circleDiameter = m_circle.getRadius() * 2.f;
    float radius = m_circle.getRadius();

    sf::Vector2f center(radius, (totalHeight - circleDiameter) / 2.f + radius);
    float distanceSq = (x - center.x) * (x - center.x) + (y - center.y) * (y - center.y);

    if (distanceSq <= radius * radius) {
        return true;
    }
    return m_text.getGlobalBounds().contains({x, y});
}

void RadioButton::onKeyPressed(const sf::Event::KeyPressed& key)
{
    if (key.code == sf::Keyboard::Key::Space || key.code == sf::Keyboard::Key::Enter) {
        m_checked = !m_checked;
        triggerCallback();
    }
}

void RadioButton::onMousePressed(float x, float y)
{
    float totalHeight = Theme::getBoxHeight();
    float circleDiameter = m_circle.getRadius() * 2.f;
    float radius = m_circle.getRadius();

    sf::Vector2f center(radius, (totalHeight - circleDiameter) / 2.f + radius);

    float distanceSq = (x - center.x) * (x - center.x) + (y - center.y) * (y - center.y);

    if (distanceSq <= radius * radius) {
        m_checked = !m_checked;
        triggerCallback();
    }
}

void RadioButton::onMouseReleased(float x, float y)
{

}

void RadioButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_circle, states);

    if (m_checked) {
        target.draw(m_indicator, states);
    }

    target.draw(m_text, states);
}

} // namespace gui

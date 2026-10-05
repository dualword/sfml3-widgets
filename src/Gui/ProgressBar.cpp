/*
 * This file is part of sfml3-widgets (https://github.com/dualword/sfml3-widgets)
 * License: MIT
 */

#include "ProgressBar.hpp"
#include "Theme.hpp"

namespace gui
{

ProgressBar::ProgressBar(float length, Orientation orientation, LabelPlacement labelPlacement):
    m_box(Box::Input),
    m_orientation(orientation),
    m_labelPlacement(labelPlacement),
    m_value(0.f)
{
    if (orientation == Horizontal)
    {
        m_box.setSize(length, Theme::getBoxHeight());
    }
    else
    {
        m_box.setSize(Theme::getBoxHeight(), length);
        if (m_labelPlacement == LabelOver)
            m_label.setRotation(sf::degrees(90.f));
    }

    m_label.setString("100%");
    m_label.setFont(Theme::getFont());
    m_label.setFillColor(Theme::input.textColor);
    m_label.setCharacterSize(Theme::textSize);

    // Build bar
    const float x1 = Theme::PADDING;
    const float y1 = Theme::PADDING;
    const float x2 = (orientation == Horizontal ? length : Theme::getBoxHeight()) - Theme::PADDING;
    const float y2 = (orientation == Horizontal ? Theme::getBoxHeight() : length) - Theme::PADDING;

    sf::Vector2f posTopLeft(x1, y1);
    sf::Vector2f posTopRight(x2, y1);
    sf::Vector2f posBottomRight(x2, y2);
    sf::Vector2f posBottomLeft(x1, y2);

    const sf::IntRect& rect = Theme::getProgressBarTextureRect();
    float tx1 = static_cast<float>(rect.position.x);
    float ty1 = static_cast<float>(rect.position.y);
    float tx2 = static_cast<float>(rect.position.x + rect.size.x);
    float ty2 = static_cast<float>(rect.position.y + rect.size.y);

    sf::Vector2f texTopLeft(tx1, ty1);
    sf::Vector2f texTopRight(tx2, ty1);
    sf::Vector2f texBottomRight(tx2, ty2);
    sf::Vector2f texBottomLeft(tx1, ty2);

    m_bar[0].position = posTopLeft;     m_bar[0].texCoords = texTopLeft;
    m_bar[1].position = posTopRight;    m_bar[1].texCoords = texTopRight;
    m_bar[2].position = posBottomRight; m_bar[2].texCoords = texBottomRight;
    m_bar[3].position = posTopLeft;     m_bar[3].texCoords = texTopLeft;
    m_bar[4].position = posBottomRight; m_bar[4].texCoords = texBottomRight;
    m_bar[5].position = posBottomLeft;  m_bar[5].texCoords = texBottomLeft;

    float labelWidth = m_label.getLocalBounds().size.x;
    float labelHeight = m_label.getLocalBounds().size.y;
    if (m_labelPlacement == LabelOutside)
    {
        if (orientation == Horizontal)
        {
            // Place label on the right of the bar
            m_label.setPosition({length + Theme::PADDING, Theme::PADDING});
            setSize(length + Theme::PADDING + labelWidth, m_box.getSize().y);
        }
        else
        {
            // Place label below the bar
            setSize(m_box.getSize().x, length + Theme::PADDING + labelHeight);
        }
    }
    else
    {
        setSize(m_box.getSize());
    }

    setValue(m_value);
    setSelectable(false);
}

void ProgressBar::setValue(float value)
{
    m_label.setString(std::to_string((int)value) + "%");
    if (m_orientation == Horizontal)
    {
        float x = Theme::PADDING + (m_box.getSize().x - Theme::PADDING * 2) * value / 100;

        m_bar[1].position.x = x;
        m_bar[2].position.x = x;
        m_bar[4].position.x = x;

        if (m_labelPlacement == LabelOver)
        {
            m_box.centerTextHorizontally(m_label);
        }
    }
    else
    {
        float fullHeight = m_box.getSize().y - Theme::PADDING * 2;
        float y = fullHeight * value / 100;
        float targetY = (fullHeight - y) + Theme::PADDING;

        m_bar[0].position.y = targetY;
        m_bar[3].position.y = targetY;
        m_bar[1].position.y = targetY;

        if (m_labelPlacement == LabelOver)
        {
            m_box.centerTextVertically(m_label);
        }
        else if (m_labelPlacement == LabelOutside)
        {
            // Re-center label horizontally (text width can change)
            float labelX = (m_box.getSize().x - m_label.getLocalBounds().size.y) / 2;
            m_label.setPosition({labelX, m_box.getSize().y + Theme::PADDING});
        }
    }

    m_value = value;
}

float ProgressBar::getValue() const
{
    return m_value;
}

void ProgressBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_box, states);
    states.texture = &Theme::getTexture();
    target.draw(m_bar, 6, sf::PrimitiveType::Triangles, states); //target.draw(m_bar, 4, sf::Quads, states);
    if (m_labelPlacement != LabelNone)
        target.draw(m_label, states);
}

}

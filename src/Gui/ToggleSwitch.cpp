/*
 * This file is part of sfml3-widgets (https://github.com/dualword/sfml3-widgets)
 * License: MIT
 */

#include "ToggleSwitch.hpp"
#include <Gui/Theme.hpp>

namespace gui {

ToggleSwitch::ToggleSwitch(bool checked)
    : Widget(),
    m_checked(checked),
    m_box(Box::Input)
{
    float height = Theme::getBoxHeight();
    float width = height * 2.f;
    m_box.setSize(width, height);
    m_thumb.setSize({width/2, height});
    setSize(width, height);
    updateVisuals();
}

void ToggleSwitch::setChecked(bool checked) {
    if (m_checked != checked) {
        m_checked = checked;
        updateVisuals();
        triggerCallback();
    }
}

bool ToggleSwitch::isChecked() const {
    return m_checked;
}

void ToggleSwitch::onMousePressed(float x, float y) {
    m_isDragging = true;
    float centerY = 0;
    float minX = 0;
    float maxX = getSize().x/2;
    float clampedX = std::max(minX, std::min(x, maxX));
    m_thumb.setPosition({clampedX, centerY});
}

void ToggleSwitch::onMouseMoved(float x, float y) {
    if (m_isDragging) {
        float centerY = 0;
        float minX = 0;
        float maxX = getSize().x/2;
        float clampedX = std::max(minX, std::min(x, maxX));
        m_thumb.setPosition({clampedX, centerY});
    }
}

void ToggleSwitch::onMouseReleased(float x, float y) {
    if (m_isDragging) {
        m_isDragging = false;
        bool finalState = (x > (getSize().x / 2.f));
        setChecked(finalState);
        updateVisuals();
    }
}

void ToggleSwitch::onStateChanged(State state) {
    m_box.applyState(state);
}

void ToggleSwitch::updateVisuals() {
    float height = getSize().y;
    float width = getSize().x;
    float centerY = height / 2.f;

    if (m_checked) {
        m_thumb.setFillColor(Theme::click.textColor);
        m_thumb.setPosition({width/2, 0});
    } else {
        m_thumb.setFillColor(Theme::click.textColor);
        m_thumb.setPosition({0, 0});
    }
}

void ToggleSwitch::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_box, states);
    target.draw(m_thumb, states);
}

} // namespace gui

/*
 * This file is part of sfml3-widgets (https://github.com/dualword/sfml3-widgets)
 * License: MIT
 */

#pragma once

#include <Gui/Widget.hpp>
#include "Utils/Box.hpp"
#include <SFML/Graphics.hpp>

namespace gui {

class ToggleSwitch : public Widget {
public:

    ToggleSwitch(bool checked = false);
    void onStateChanged(State state) override;
    void setChecked(bool checked);
    bool isChecked() const;
    void onMousePressed(float x, float y) override;
    void onMouseMoved(float x, float y) override;
    void onMouseReleased(float x, float y) override;

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    void updateVisuals();

    bool m_checked;
    Box m_box;
    sf::RectangleShape m_thumb;
    bool m_isDragging = false;
};

} // namespace gui

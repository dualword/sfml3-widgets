/*
 * This file is part of sfml3-widgets (https://github.com/dualword/sfml3-widgets)
 * License: MIT
 */

#ifndef GUI_RADIOBUTTON_HPP
#define GUI_RADIOBUTTON_HPP

#include <Gui/Widget.hpp>
#include <SFML/Graphics/CircleShape.hpp>

namespace gui
{

class RadioButton : public Widget
{
public:
    RadioButton(const sf::String& label = "", bool checked = false);

    void setChecked(bool checked);
    bool isChecked() const;
    virtual bool isHighlighted(float x, float y) const;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void onMousePressed(float x, float y) override;
    virtual void onMouseReleased(float x, float y) override;
    virtual void onStateChanged(State state) override;
    void onKeyPressed(const sf::Event::KeyPressed& key) override;

private:
    void updateGeometry();

    bool m_checked;
    sf::CircleShape m_circle;
    sf::CircleShape m_indicator;
    sf::Text m_text;
};

} // namespace gui

#endif // GUI_RADIOBUTTON_HPP

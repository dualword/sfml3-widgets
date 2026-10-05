/*
 * This file is part of sfml3-widgets (https://github.com/dualword/sfml3-widgets)
 * License: MIT
 */

#ifndef GUI_SPRITEBUTTON_HPP
#define GUI_SPRITEBUTTON_HPP

#include "Widget.hpp"
#include "Theme.hpp"

namespace gui
{

/**
 * Push button linked to a sprite sheet
 */
class SpriteButton: public Widget
{
public:
    SpriteButton(const sf::Texture& texture, const sf::String& label = "");

    void setString(const sf::String& string);
    const sf::String& getString() const;

    void setFont(const sf::Font& font);
    const sf::Font& getFont() const;

    void setTextSize(size_t size);

    void setTexture(const sf::Texture& texture);

    void onStateChanged(State state) override;
    void onMouseMoved(float x, float y) override;
    void onMousePressed(float x, float y) override;
    void onMouseReleased(float x, float y) override;
    void onKeyPressed(const sf::Event::KeyPressed& key) override;
    void onKeyReleased(const sf::Event::KeyPressed& key) override;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void press();
    void release();

    sf::Text m_text{gui::Theme::getFont()};
    sf::Sprite m_background;
    bool m_pressed;
};

}

#endif // GUI_SPRITEBUTTON_HPP

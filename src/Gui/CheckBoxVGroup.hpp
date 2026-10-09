/*
 * This file is part of sfml3-widgets (https://github.com/dualword/sfml3-widgets)
 * License: MIT
 */

#pragma once
#include <vector>
#include <string>
#include <functional>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Gui/Layouts/VBoxLayout.hpp"
#include "Gui/CheckBox.hpp"
#include "Gui/Label.hpp"
#include "Gui/Layouts/HBoxLayout.hpp"

class CheckBoxVGroup : public gui::VBoxLayout {
private:
    std::vector<gui::CheckBox*> m_buttons;
    gui::CheckBox* m_selectedButton = nullptr;
    std::function<void(int)> m_onChangedCallback = nullptr;
    bool m_isUpdating = false;
    gui::Label* m_headerLabel = nullptr;
    bool m_hasBorder = true;
    float m_borderThickness = 2.f;
    sf::Color m_borderColor = sf::Color(150, 150, 150);
    float m_padding = 8.f;

public:
    CheckBoxVGroup() : gui::VBoxLayout() {}

    void setHeader(const std::string& text) {
        if (!m_headerLabel) {
            m_headerLabel = new gui::Label(text);
            this->add(m_headerLabel);
        } else {
            m_headerLabel->setText(text);
        }
    }

    void setBorder(bool enable, sf::Color color = sf::Color(150, 150, 150), float thickness = 2.f, float padding = 8.f) {
        m_hasBorder = enable;
        m_borderColor = color;
        m_borderThickness = thickness;
        m_padding = padding;
    }

    void addOption(const std::string& text) {
        gui::HBoxLayout* row = new gui::HBoxLayout();
        gui::CheckBox* checkbox = new gui::CheckBox();
        gui::Label* label = new gui::Label(text);

        row->add(checkbox);
        row->add(label);
        this->add(row);

        m_buttons.push_back(checkbox);
        int index = static_cast<int>(m_buttons.size()) - 1;

        checkbox->setCallback([this, checkbox, index]() {
            if (m_isUpdating) return;
            m_isUpdating = true;

            if (checkbox == m_selectedButton && !checkbox->isChecked()) {
                checkbox->check(true);
            } else if (checkbox->isChecked()) {
                for (auto* btn : m_buttons) {
                    if (btn != checkbox) btn->check(false);
                }
                m_selectedButton = checkbox;

                if (m_onChangedCallback) {
                    m_onChangedCallback(index);
                }
            }
            m_isUpdating = false;
        });

        if (m_buttons.size() == 1) {
            select(0);
        }
    }

    void select(int index) {
        if (index >= 0 && index < static_cast<int>(m_buttons.size())) {
            m_buttons[index]->check(true);
        }
    }

    int getSelectedIndex() const {
        for (int i = 0; i < static_cast<int>(m_buttons.size()); ++i) {
            if (m_buttons[i] == m_selectedButton) return i;
        }
        return -1;
    }

    void setOnChanged(std::function<void(int index)> callback) {
        m_onChangedCallback = callback;
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        gui::VBoxLayout::draw(target, states);

        if (m_hasBorder) {
            sf::Vector2f pos = this->getPosition();
            sf::Vector2f size = this->getSize();

            float topOffset = 0.f;
            if (m_headerLabel) {
                topOffset = m_headerLabel->getSize().y + m_padding;
            }

            sf::RectangleShape border;
            border.setPosition({pos.x - m_padding, pos.y - m_padding + topOffset});
            border.setSize(sf::Vector2f(size.x + (m_padding * 2), size.y + (m_padding * 2) - topOffset));
            border.setFillColor(sf::Color::Transparent);
            border.setOutlineColor(m_borderColor);
            border.setOutlineThickness(m_borderThickness);
            target.draw(border, states);
        }
    }
};

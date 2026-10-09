/*
 * This file is part of sfml3-widgets (https://github.com/dualword/sfml3-widgets)
 * License: MIT
 */

#pragma once
#include <vector>
#include <functional>
#include "Gui/CheckBox.hpp"

class CheckBoxGroup {
private:
    std::vector<gui::CheckBox*> m_buttons;
    gui::CheckBox* m_selectedButton = nullptr;
    std::function<void(gui::CheckBox*, int)> m_onChangedCallback = nullptr;
    bool m_isUpdating = false;

public:
    CheckBoxGroup() = default;

    void addButton(gui::CheckBox* checkbox) {
        if (!checkbox) return;

        m_buttons.push_back(checkbox);
        int index = static_cast<int>(m_buttons.size()) - 1;

        if (!m_selectedButton && checkbox->isChecked()) {
            m_selectedButton = checkbox;
        }

        checkbox->setCallback([this, checkbox, index]() {
            if (m_isUpdating) return;

            m_isUpdating = true;
            if (checkbox == m_selectedButton && !checkbox->isChecked()) {
                checkbox->check(true);
            } else if (checkbox->isChecked()) {
                for (auto* btn : m_buttons) {
                    if (btn != checkbox) {
                        btn->check(false);
                    }
                }
                m_selectedButton = checkbox;
                if (m_onChangedCallback) {
                    m_onChangedCallback(m_selectedButton, index);
                }
            }

            m_isUpdating = false;
        });
    }

    void select(int index) {
        if (index >= 0 && index < static_cast<int>(m_buttons.size())) {
            m_buttons[index]->check(true);
        }
    }

    gui::CheckBox* getSelectedButton() const {
        return m_selectedButton;
    }

    int getSelectedIndex() const {
        for (int i = 0; i < static_cast<int>(m_buttons.size()); ++i) {
            if (m_buttons[i] == m_selectedButton) return i;
        }
        return -1;
    }

    void setCallback(std::function<void(gui::CheckBox* selected, int index)> callback) {
        m_onChangedCallback = callback;
    }
};

/*
 * This file is part of sfml3-widgets (https://github.com/dualword/sfml3-widgets)
 * License: MIT
 */

#include "RadioButtonGroup.hpp"

namespace gui
{

RadioButtonGroup::RadioButtonGroup()
    : m_selectedId(-1)
{
}

void RadioButtonGroup::addButton(RadioButton* button, int id)
{
    if (!button) return;
    m_buttons.push_back({button, id});
    if (button->isChecked()) {
        m_selectedId = id;
    }

    button->setCallback([this, id]() {
        if (id != m_selectedId) {
            this->handleSelection(id);
        } else {
            for (auto& item : m_buttons) {
                if (item.id == m_selectedId) {
                    item.button->setChecked(true);
                }
            }
        }
    });
    if (button->isChecked()) {
        handleSelection(m_selectedId);
    }
}

void RadioButtonGroup::selectButton(int id)
{
    handleSelection(id);
}

int RadioButtonGroup::getSelectedId() const
{
    return m_selectedId;
}

void RadioButtonGroup::setCallback(std::function<void(int)> callback)
{
    m_groupCallback = callback;
}

void RadioButtonGroup::handleSelection(int selectedId)
{
    m_selectedId = selectedId;
    for (auto& item : m_buttons) {
        if (item.id == m_selectedId) {
            item.button->setChecked(true);
        } else {
            item.button->setChecked(false);
        }
    }

    if (m_groupCallback) {
        m_groupCallback(m_selectedId);
    }
}

} // namespace gui


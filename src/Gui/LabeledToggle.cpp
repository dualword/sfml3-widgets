/*
 * This file is part of sfml3-widgets (https://github.com/dualword/sfml3-widgets)
 * License: MIT
 */

#include "LabeledToggle.hpp"
#include <Gui/Theme.hpp>

namespace gui {

LabeledToggle::LabeledToggle(const std::string& labelText, bool checked) : Layout()
{
    m_label  = new Label(labelText);
    add(m_label);
    m_switch = new ToggleSwitch(checked);
    add(m_switch);

    float spacing = Theme::MARGIN;
    float height = Theme::getBoxHeight();
    m_label->setPosition({0.f, (height - m_label->getSize().y) / 2.f});
    m_switch->setPosition({m_label->getSize().x + spacing, 0.f});
    float totalWidth = m_label->getSize().x + spacing + m_switch->getSize().x;
    setSize(totalWidth, height);
}

void LabeledToggle::setChecked(bool checked) {
    m_switch->setChecked(checked);
}

bool LabeledToggle::isChecked() const {
    return m_switch->isChecked();
}

void LabeledToggle::setCallback(std::function<void(void)> callback){
    m_switch->setCallback(callback);
}

void LabeledToggle::setText(const std::string& text) {
    m_label->setText(text);
    float spacing = Theme::MARGIN;
    m_switch->setPosition({m_label->getSize().x + spacing, 0.f});
    setSize(m_label->getSize().x + spacing + m_switch->getSize().x, Theme::getBoxHeight());
}

} // namespace gui


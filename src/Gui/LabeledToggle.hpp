/*
 * This file is part of sfml3-widgets (https://github.com/dualword/sfml3-widgets)
 * License: MIT
 */

#pragma once

#include <Gui/Layouts/Layout.hpp>
#include <Gui/Label.hpp>
#include "Gui/ToggleSwitch.hpp"
#include <string>

namespace gui {

class LabeledToggle : public Layout {
public:
    LabeledToggle(const std::string& labelText, bool checked = false);
    void setChecked(bool checked);
    bool isChecked() const;
    void setText(const std::string& text);
    void setCallback(std::function<void(void)> callback);

private:
    Label* m_label;
    ToggleSwitch* m_switch;
};

} // namespace gui

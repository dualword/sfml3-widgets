/*
 * This file is part of sfml3-widgets (https://github.com/dualword/sfml3-widgets)
 * License: MIT
 */

#ifndef GUI_RADIOBUTTONGROUP_HPP
#define GUI_RADIOBUTTONGROUP_HPP

#include "RadioButton.hpp"
#include <vector>
#include <functional>

namespace gui
{

class RadioButtonGroup
{
public:
    RadioButtonGroup();
    void addButton(RadioButton* button, int id);
    void selectButton(int id);
    int getSelectedId() const;
    void setCallback(std::function<void(int)> callback);

private:
    void handleSelection(int selectedId);

    struct GroupItem {
        RadioButton* button;
        int id;
    };

    std::vector<GroupItem> m_buttons;
    int m_selectedId;
    std::function<void(int)> m_groupCallback;
};

} // namespace gui

#endif // GUI_RADIOBUTTONGROUP_HPP


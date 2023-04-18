/*
 * Rosalie's Mupen GUI - https://github.com/Rosalie241/RMG
 *  Copyright (C) 2020 Rosalie Wanders <rosalie@mailbox.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 3.
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef ADDMAPPINGBUTTON_HPP
#define ADDMAPPINGBUTTON_HPP

#include <QPushButton>

#include "common.hpp"

namespace UserInterface
{
namespace Widget
{

// we can't include ControllerWidget.hpp
// because that header includes this header,
// so forward-declare it to prevent issues
class ControllerWidget;
class MappingButton;

class AddMappingButton : public QPushButton
{
private:
    ControllerWidget* controllerWidget = nullptr;
    MappingButton* mappingButton       = nullptr;

public:
    AddMappingButton(QWidget* parent);
    ~AddMappingButton();

    void Initialize(ControllerWidget* widget, MappingButton* button);
};
}
}

#endif // ADDMAPPINGBUTTON_HPP

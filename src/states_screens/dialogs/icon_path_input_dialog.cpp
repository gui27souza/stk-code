//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2010-2015 Marianne Gagnon
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include "states_screens/dialogs/icon_path_input_dialog.hpp"

#include "guiengine/widgets/ribbon_widget.hpp"
#include "guiengine/widgets/text_box_widget.hpp"
#include "states_screens/state_manager.hpp"

using namespace GUIEngine;

// ----------------------------------------------------------------------------
IconPathInputDialog::IconPathInputDialog(PlayerProfile* pp, BaseUserScreen* user_screen)
                     : ModalDialog(0.6f, 0.4f, MODAL_DIALOG_LOCATION_CENTER)
{
    loadFromFile("icon_path_input_dialog.stkgui");

    m_player_profile = pp;
    m_parent_screen = user_screen;

    m_is_valid_icon_path = false;

    m_buttons_widget = getWidget<RibbonWidget>("buttons");
    assert(m_buttons_widget);

    m_path_input_buttons_widget = getWidget<RibbonWidget>("path_input_buttons");
    assert(m_buttons_widget);

    m_icon_path_textbox_widget = getWidget<TextBoxWidget>("icon_path_textbox");
    assert(m_icon_path_textbox_widget);

    m_icon_path_output_widget = getWidget<TextBoxWidget>("icon_path_output");
    assert(m_icon_path_output_widget);

}   // IconPathInputDialog

// ----------------------------------------------------------------------------
IconPathInputDialog::~IconPathInputDialog()
{}   // ~IconPathInputDialog

// ----------------------------------------------------------------------------
void IconPathInputDialog::init()
{
    ModalDialog::init();
}


// ----------------------------------------------------------------------------
void IconPathInputDialog::beforeAddingWidgets()
{

    m_buttons_widget = getWidget<RibbonWidget>("buttons");
    assert(m_buttons_widget);
    int apply_button_index = m_buttons_widget->findItemNamed("apply");
    m_apply_button = &m_buttons_widget->getChildren()[apply_button_index];
    assert(m_apply_button);
    m_apply_button->setActive(false);


    m_icon_path_output_widget = getWidget<TextBoxWidget>("icon_path_output");
    assert(m_icon_path_output_widget);
    m_icon_path_output_widget->setActive(false);

    RibbonWidget* icon_render_buttons = getWidget<RibbonWidget>("icon_render_buttons");
    assert(icon_render_buttons);
    int icon_render_index = icon_render_buttons->findItemNamed("icon_render");
    m_icon_render = &icon_render_buttons->getChildren()[icon_render_index];
    assert(m_icon_render);
    m_icon_render->setActive(false);

}   // beforeAddingWidgets

// ----------------------------------------------------------------------------
bool IconPathInputDialog::validatePath()
{
    // TODO - IconPathInputDialog::validatePath
    // If an error occur, report to the user

    stringw a = getWidget<TextBoxWidget>("icon_path_textbox")->getText();

    // Validate path

    return true;
}   // validatePath

// ----------------------------------------------------------------------------
void IconPathInputDialog::renderNewIcon()
{
    // TODO - IconPathInputDialog::renderNewIcon
    // Render new incon in m_icon_render

}   // renderNewIcon

// ----------------------------------------------------------------------------
GUIEngine::EventPropagation
            IconPathInputDialog::processEvent(const std::string& eventSource)
{

    if (eventSource == "path_input_buttons")
    {
        const std::string& selection = m_path_input_buttons_widget->
                                    getSelectionIDString(PLAYER_ID_GAME_MASTER);

        if (selection == "validate") {
            m_is_valid_icon_path = validatePath();

            if (m_is_valid_icon_path) {
                renderNewIcon();
                m_icon_render->setActive(true);
                m_icon_path_output_widget->setText("Valid icon path!");
                m_apply_button->setActive(true);
            }
        }
    }

    if (eventSource == "buttons")
    {

        const std::string& selection = m_buttons_widget->
                                    getSelectionIDString(PLAYER_ID_GAME_MASTER);

        if (selection == "apply")
        {

            if (m_is_valid_icon_path && !m_icon_path.empty())
            {
                m_player_profile->setIconFromPath(m_icon_path);
                m_parent_screen->loadProfilesIcons();
            }

            ModalDialog::dismiss();
            return GUIEngine::EVENT_BLOCK;
        }
        else if (selection == "cancel")
        {
            ModalDialog::dismiss();
            return GUIEngine::EVENT_BLOCK;
        }
    }
    return GUIEngine::EVENT_LET;
}   // processEvent

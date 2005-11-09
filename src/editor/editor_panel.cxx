//  $Id: editor_panel.cxx,v 1.00 2005/11/07 23:41:12 Jave27 Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 1999 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
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

#include <ClanLib/Display/color.h>
#include <vector>
#include "../resource.hxx"
#include "../vector.hxx"
#include "../display/drawing_context.hxx"
#include "../gui/gui_manager.hxx"
#include "editor_panel.hxx"
#include "editor_screen.hxx"
#include "panel_buttons.hxx"

namespace Pingus {

	class GUI::Component;

namespace Editor {

// Constructor
EditorPanel::EditorPanel(EditorScreen* es)
: editor(es)
{

}

// Destructor
EditorPanel::~EditorPanel()
{

}

// Wait to run this until after the panel has been added to the gui_manager
// This sets up the buttons, text fields, etc. for this panel
// No need to delete the buttons because the gui_manager will do it for us.
void
EditorPanel::init()
{
	// Create exit button
	add((PanelButton*)(new PanelButtonExit(this)));
}

// Draw the panel
void
EditorPanel::draw (DrawingContext& gc)
{
	gc.draw_fillrect(0.0f, 0.0f, (float)CL_Display::get_width(), 
		50.0f, CL_Color::lightgray);
}

// Add the button to the vector, set it's position, and add to the gui_manager
void
EditorPanel::add(PanelButton* button)
{
	// Determind where to place this buttons
	Vector new_pos;

	if (panel_buttons.empty())
		new_pos = Vector(0.0f, 0.0f, 0.0f);
	else
		new_pos = Vector((*panel_buttons.end())->get_pos() + 
			Vector((float)(5 + (*panel_buttons.end())->get_width()), 0.0f));
	// Add button to collection of buttons
	panel_buttons.push_back(button);
	
	// Add a 5 pixel spacing between all buttons
	button->set_pos(new_pos);

	// Add the button to the GUI Manager
	get_screen()->get_gui_manager()->add((GUI::Component*)button);
}

} // Editor namespace
} // Pingus namespace
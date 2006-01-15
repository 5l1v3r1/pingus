//  $Id: editor_screen.cxx,v 1.00 2005/11/07 23:41:12 Jave27 Exp $
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

#include <iostream>
#include <ClanLib/Core/System/clanstring.h>
#include "../system.hxx"
#include "../sound/sound.hxx"
#include "../gui/gui_manager.hxx"
#include "../gui/screen_manager.hxx"
#include "../display/drawing_context.hxx"
#include "../res_descriptor.hxx"
#include "../resource.hxx"
#include "../fonts.hxx"
#include "../file_dialog.hxx"
#include "../path_manager.hxx"
#include "editor_screen.hxx"
#include "editor_panel.hxx"
#include "editor_viewport.hxx"
#include "xml_level.hxx"
#include "level_objs.hxx"

namespace Pingus {

namespace Editor {

// Default constructor
EditorScreen::EditorScreen(XMLLevel* level)
: plf(level), 
	close_dialog(false),
	filedialog(0)
{
	if (!plf) plf = new XMLLevel();
}

// Destructor
EditorScreen::~EditorScreen()
{
	delete plf;
	if (filedialog)
		delete filedialog;
}

// Startup code
void
EditorScreen::on_startup()
{
	// Create the viewport for the images and data
	viewport = new EditorViewport(this);
	gui_manager->add(viewport);	
	
	// Create the panel for the buttons
	panel = new EditorPanel(this);
	gui_manager->add(panel);
	panel->init();

}

// Close the current screen
void
EditorScreen::close_screen()
{
	ScreenManager::instance()->pop_screen();
}

// Escape was pressed
void
EditorScreen::on_escape_press()
{
  close_screen();
}

// Show dialog box
void
EditorScreen::show_file_dialog(bool for_loading)
{
	if (filedialog)
		delete filedialog;
	close_dialog = false;
	filedialog = new FileDialog(this, ".pingus", 
		path_manager.complete("levels/"), for_loading);
	filedialog->preload();	
}

// Close dialog box
void
EditorScreen::cancel()
{
	close_dialog = true;
}

// Save the current level
void 
EditorScreen::save(const std::string &file, const std::string &filemask)
{
	close_dialog = true;
	plf->save_level(file);
	panel->set_selected_button(0);
}

// Load a new level
void 
EditorScreen::load(const std::string &file, const std::string &filemask)
{
	close_dialog = true;
	plf->load_level(file);
	viewport->refresh();
	panel->set_selected_button(0);
}

// Play the current level (save to a temporary file 
// then load it normally)
void
EditorScreen::play_level()
{
	// Ask, "Would you like to save first?".
	// if so, save the file normally.

	// Then save to a temporary file

	// Load the temporary file
}

// Draw the background and components
bool
EditorScreen::draw(Pingus::DrawingContext &gc)
{
	// Black out screen
	gc.draw_fillrect(0, 0, (float)CL_Display::get_width(), 
		(float)CL_Display::get_height(), CL_Color::black, -10000);
	gui_manager->draw(gc);

	// FIXME: Remove this warning
	gc.print_center(Fonts::pingus_large, (float)(CL_Display::get_width() / 2), 
		(float)(CL_Display::get_height() / 2), "Not yet functional");
		
	if (filedialog)
		filedialog->draw(gc);
	
	return true;
}

void
EditorScreen::update(const GameDelta &delta)
{
	if (filedialog)
	{
		if (close_dialog)
		{
			delete filedialog;
			filedialog = 0;
		}
		else
			filedialog->update(delta);
	}
	else
		GUIScreen::update(delta);

}

} // Editor namespace
} // Pingus namespace

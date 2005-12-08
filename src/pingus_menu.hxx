//  $Id: pingus_menu.hxx,v 1.12 2003/10/18 23:17:27 grumbel Exp $
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

#ifndef HEADER_PINGUS_PINGUS_MENU_HXX
#define HEADER_PINGUS_PINGUS_MENU_HXX

#include "fonts.hxx"
#include "pingus_sub_menu.hxx"
#include "layer_manager.hxx"

class CL_Key;
class CL_InputDevice;

namespace Pingus {

class SurfaceButton;
class GameDelta;

namespace GUI {
class GUIManager;
} // namespace GUI

class MenuButton;

class PingusMenu : public PingusSubMenu
{
public:
  bool is_init;
private:
  std::vector<CL_Slot> slots;

  CL_Sprite background;
  LayerManager layer_manager;
  CL_Surface cursor_sur;

  MenuButton* start_button;
  MenuButton* quit_button;

  MenuButton* contrib_button;
  MenuButton* story_button;
  MenuButton* multiplayer_button;
	MenuButton* editor_button;
  
  void on_resize (int w, int h);

  // These functions setup the different menus
  void setup_main_menu();
  void setup_game_menu();
	/** Show the levels folder */
  void setup_contrib_menu();
	/** Show the worldmap folder */
	void setup_worldmap_menu();

	/** Quit the game */
  void do_quit();
	/** Start the story/worldmap mode */
	void do_start(const std::string &filename);
	/** Start the level editor */
	void do_edit();

	/** Use this to load the level or worldmap */
	virtual void load(const std::string &file, const std::string &filemask);

public:
  PingusMenu (PingusMenuManager* m);
  ~PingusMenu();

  /// Load all images and other stuff for the menu
  void preload ();
  void do_contrib(const std::string&);

  void on_escape_press ();
  void draw_foreground(DrawingContext& gc);
private:
  PingusMenu (const PingusMenu&);
  PingusMenu& operator= (const PingusMenu&);
};

} // namespace Pingus

#endif

/* EOF */

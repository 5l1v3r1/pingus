//  $Id: pingus_menu_manager.hxx,v 1.4 2002/07/30 01:58:16 grumbel Exp $
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_PINGUS_MENU_MANAGER_HXX
#define HEADER_PINGUS_PINGUS_MENU_MANAGER_HXX

#include "menu_background.hxx"
#include "exit_menu.hxx"
#include "story.hxx"
#include "pingus_menu.hxx"
#include "intro.hxx"
#include "option_menu.hxx"

class PingusSubMenu;

class PingusMenuManager
{
private:
  /** Menu stack. the menu on top is .end (), the bottom menu .begin () */
  std::vector<PingusSubMenu *> menu_stack;
  typedef std::vector<PingusSubMenu *>::iterator MenuStackIter;
  typedef std::vector<PingusSubMenu *>::reverse_iterator MenuStackRIter;

  bool loop;

  int event_register_counter;
  
  /// Register all event-handling stuff
  void register_events ();

  /// Unregister all event-handling stuff
  void unregister_events ();
public:
  /* Menu's */
  Intro intro;
  PingusMenu mainmenu;
  OptionMenu optionmenu;
  MenuBackground background;
  Story story;
  ExitMenu exitmenu;

  PingusMenuManager ();
  ~PingusMenuManager ();

  void draw ();
  void update (float delta);

  /// Display the menu (this is basically the game's main loop)
  void display ();

  /// Disable events
  void enable_events ();
  /// Enable events
  void disable_events ();

  void fadeout ();

  // !FIXME! Should use controller instead
  /*
  void on_button_press (CL_InputDevice*,const CL_Key &);
  void on_button_release (CL_InputDevice*,const CL_Key &);
  void on_mouse_move (CL_InputDevice*, int, int);
  */

  /// Exit the menu manager (which means to exit the while() loop in display ())
  void exit ();

  PingusSubMenu * current_menu();

  // Replace the current menu with a new one
  void set_menu (PingusSubMenu * menu);
  /** Remove the current menu and fall back to the last one.
      This is used for yes/no dialoges and such things. */
  void pop_menu ();
  
  /** Add's a new menu to the menu stack. This is used for yes/no
      dialoges and such things.*/
  void push_menu (PingusSubMenu * menu);
};

#endif

/* EOF */

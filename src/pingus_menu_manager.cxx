//  $Id: pingus_menu_manager.cxx,v 1.8 2002/08/03 17:20:37 grumbel Exp $
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

#include <ClanLib/Display/Input/input.h>
#include <ClanLib/Display/Input/keyboard.h>
#include "globals.hxx"
#include "display.hxx"
#include "delta_manager.hxx"
#include "fade_out.hxx"
#include "input/controller.hxx"
#include "screen_manager.hxx"
#include "pingus_menu_manager.hxx"

PingusMenuManager* PingusMenuManager::instance_ = 0;

PingusMenuManager::PingusMenuManager ()
  : event_register_counter (0),
    intro (this), mainmenu (this), optionmenu (this), story (this),
    exitmenu (this)
{
  //current_menu = 0;
  if (intro_disabled)
    push_menu (&mainmenu);
  else
    push_menu (&intro); 
}

PingusMenuManager::~PingusMenuManager ()
{
}

/// Register all event-handling stuff
void 
PingusMenuManager::register_events ()
{
  //FIXME: I don't like event handling in pingus, should be handled
  //FIXME: otherwise. 

  if (event_register_counter == 0)
    {
      ++event_register_counter;
      
      /*
      on_button_press_slot
	= CL_Input::sig_button_press ().connect (this, &PingusMenuManager::on_button_press);
      on_button_release_slot
	= CL_Input::sig_button_release ().connect (this, &PingusMenuManager::on_button_release);
      on_mouse_move_slot
	= CL_Input::sig_mouse_move ().connect (this, &PingusMenuManager::on_mouse_move);
      */
    }
  else
    {
      std::cout << "PingusMenuManager::register_events (): handler already registered" << std::endl;
    }
}

void 
PingusMenuManager::unregister_events ()
{
  /*
  CL_Input::sig_button_press ().disconnect (on_button_press_slot);
  CL_Input::sig_button_release ().disconnect (on_button_release_slot);
  CL_Input::sig_mouse_move ().disconnect (on_mouse_move_slot);
  */
}

void 
PingusMenuManager::enable_events ()
{
  ++event_register_counter;
}

void 
PingusMenuManager::disable_events ()
{
  --event_register_counter;
}

/*
void 
PingusMenuManager::on_button_press (CL_InputDevice* device,const CL_Key& key)
{
  if (event_register_counter <= 0) return;

  std::cout << "PingusMenuManager::on_button_press (" 
	    << device << ", " << key.id 
	    << ")" << std::endl;
  if (device == CL_Input::keyboards[0] && key.id == CL_KEY_ESCAPE)
    {
      if (menu_stack.size () > 2)
	pop_menu ();
      else if (menu_stack.size () == 2 && current_menu () != &mainmenu)
	set_menu (&mainmenu);
      else if (menu_stack.size () == 2 && current_menu () == &mainmenu)
	push_menu (&exitmenu);
    }
  else
    current_menu ()->on_button_press (device, key);
}

void
PingusMenuManager::on_button_release (CL_InputDevice* device,const CL_Key& key)
{
  if (event_register_counter <= 0) return;
  current_menu ()->on_button_release (device, key);
}

void 
PingusMenuManager::on_mouse_move (CL_InputDevice* device, int x, int y)
{
  if (event_register_counter <= 0) return;
  //  std::cout << "PingusMenuManager::on_mouse_move ("
  //<< device << ", " << x << ", " << y << ")" << std::endl;
  current_menu ()->on_mouse_move (device, x, y);
}
*/

/*
void 
PingusMenuManager::display ()
{
  //std::cout << "Pingusmenumanager: display ()" << std::endl;
  DeltaManager delta_manager;

  current_menu ()->preload ();
  register_events ();
  loop = true;

  Input::Controller input_controller("../doc/mycontroller.xml");
  // Main loop for the menu
  while (loop)
    {
      //std::cout << "Displaying menu..." << std::endl;
      float time_delta = delta_manager.getset ();

      input_controller.update (time_delta);

      // We ignore delta's larger then one second, to avoid jumps in
      // the scrolling (for example when starting a level and then
      // after some minutes going back to the menu would cause delta's
      // from >100, not nice)

      GameDelta delta (time_delta, input_controller.get_events ());

      // We copy the menu_stack so that we don't invalidate our
      // iterators when menu's are removed/added in update()
      std::vector<PingusSubMenu *> tmp_menu_stack = menu_stack;

      for (MenuStackIter i = tmp_menu_stack.begin (); i != tmp_menu_stack.end (); ++i)
	(*i)->draw ();

      for (MenuStackIter i = tmp_menu_stack.begin (); i != tmp_menu_stack.end (); ++i)
	(*i)->update (delta);
      
      Display::flip_display ();

      
      CL_System::keep_alive ();
      CL_System::sleep (0);
    }
  unregister_events ();
}
*/
void
PingusMenuManager::draw ()
{
  background.draw ();

  for (MenuStackIter i = menu_stack.begin (); i != menu_stack.end (); ++i)
    (*i)->draw ();
}

void
PingusMenuManager::update (const GameDelta& delta)
{
  background.update (delta.get_time ());
  // We copy the menu_stack so that we don't invalidate our
  // iterators when menu's are removed/added in update()
  std::vector<PingusSubMenu *> tmp_menu_stack = menu_stack;

  /*for (MenuStackIter i = tmp_menu_stack.begin (); i != tmp_menu_stack.end (); ++i)
    (*i)->update (delta);*/
  menu_stack.back ()->update (delta);
}

void 
PingusMenuManager::set_menu (PingusSubMenu * menu)
{
  /*if (current_menu.get ())
    fadeout ();*/
  pop_menu ();
  push_menu (menu);
  //current_menu = menu;
  //current_menu->preload ();
}

void 
PingusMenuManager::push_menu (PingusSubMenu * menu)
{
  menu->preload ();
  menu_stack.push_back (menu);
}

void 
PingusMenuManager::pop_menu ()
{
  if (!menu_stack.empty ())
    menu_stack.pop_back();
}

PingusSubMenu *
PingusMenuManager::current_menu ()
{
  if (!menu_stack.empty ())
    {
      MenuStackRIter i = menu_stack.rbegin ();
      if (! *i)
	std::cout << "PingusMenuManager: Error: current_menu is " << *i << std::endl;
      return *i;
    }
  else
    {
      std::cout << "PingusMenuManager: Error: MenuStack empty!" << std::endl;
      return 0;
    }
}

void 
PingusMenuManager::fadeout ()
{
  std::cout << "PingusMenuManager::fadeout () Not implemented" << std::endl;
  DeltaManager delta_manager;
  EnlargingRectFadeOut fadeout;

  while (!fadeout.finished ())
    {
      float time_delta = delta_manager.getset ();
      fadeout.update (time_delta);

      current_menu ()->draw ();
      fadeout.draw ();
      Display::flip_display ();

      CL_System::keep_alive ();
    }
}

void
PingusMenuManager::show_exit_menu ()
{
  push_menu (&exitmenu);
}

void
PingusMenuManager::exit ()
{
  std::cout << "poping PingusMenuManager" << std::endl;
  ScreenManager::instance ()->pop_screen ();
}

PingusMenuManager*
PingusMenuManager::instance ()
{
  if (instance_)
    return instance_;
  else
    return instance_ = new PingusMenuManager ();
}

/* EOF */

//  $Id: screen_manager.cxx,v 1.13 2002/08/17 12:32:23 grumbel Exp $
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

#include <iostream>
#include <ClanLib/Display/Display/display.h>
#include "globals.hxx"
#include "input/controller.hxx"
#include "delta_manager.hxx"
#include "game_delta.hxx"
#include "screen.hxx"
#include "display.hxx"
#include "pingus_menu_manager.hxx"
#include "screen_manager.hxx"
#include "path_manager.hxx"
#include "input_debug_screen.hxx"

ScreenManager* ScreenManager::instance_ = 0;

ScreenManager::ScreenManager ()
  : last_screen (0)
{
  replace_screen_arg = std::pair<Screen*, bool>(0, false);
  cached_action = none;

  // Set the root screen
  if (!show_input_debug_screen)
    push_screen (PingusMenuManager::instance (), false);
  else
    push_screen (new InputDebugScreen (), true);
}

ScreenManager::~ScreenManager ()
{
}

void
ScreenManager::display ()
{
  Input::Controller input_controller(path_manager.complete ("controller/default.xml"));
  DeltaManager delta_manager;

  // Main loop for the menu
  while (!screens.empty())
    {
      Screen* current_screen = screens.back ().first;
      float time_delta = delta_manager.getset ();
      
      if (time_delta > 1.0)
	{
	  std::cout << "PingusMenuManager: detected large delta (" << time_delta
		    << "), ignoring and doing frameskip" << std::endl;
	  continue;
	}

      // Let ClanLib fetch events
      CL_System::keep_alive ();

      // Get new events from ClanLib
      input_controller.update (time_delta);

      // Fill the delta with values
      GameDelta delta (time_delta, input_controller.get_events ());

      last_screen = current_screen;

      // Most likly the screen will get changed in this update call
      current_screen->update (delta);    

      if (screens.empty ())
	continue;

      current_screen = screens.back ().first;

      if (cached_action == pop)
	{
	  real_pop_screen ();
	  cached_action = none;
	}
      else if (cached_action == replace)
	{
	  real_replace_screen (replace_screen_arg.first, replace_screen_arg.second);
	  cached_action = none;
	}
      
      // skip draw if the screen changed
      if (last_screen == current_screen)
      	{
	  current_screen->draw ();
	  Display::flip_display ();
	}
      else
	{
	  fade_over (last_screen, current_screen);
	}

      // Stupid hack to make this thing take less CPU
      CL_System::sleep (0);

      /** Delete all screens that are no longer needed */
      for (std::vector<Screen*>::iterator i = delete_screens.begin (); 
	   i != delete_screens.end (); 
	   ++i)
	{
	  delete *i;
	}
      delete_screens.clear ();
    } 
}

ScreenManager*
ScreenManager::instance ()
{
  if (instance_)
    return instance_;
  else
    return instance_ = new ScreenManager ();
}

void
ScreenManager::push_screen (Screen* screen, bool delete_screen)
{
  std::cout << "XXXXXXXX ScreenManager::push_screen" << std::endl;

  if (!screens.empty())
    {
      std::cout << "ScreenManager::push_screen" << std::endl;
      screens.back ().first->on_shutdown ();
    }

  screen->on_startup ();
  screens.push_back (std::pair<Screen*, bool> (screen, delete_screen));
}

void
ScreenManager::pop_screen ()
{
  assert (cached_action == none);
  cached_action = pop;
}

void
ScreenManager::replace_screen (Screen* screen, bool delete_screen)
{
  assert (cached_action == none);
  cached_action = replace;
  replace_screen_arg = std::pair<Screen*, bool> (screen, delete_screen);
}

void
ScreenManager::real_replace_screen (Screen* screen, bool delete_screen)
{
  std::cout << "XXXXXXXX ScreenManager::replace_screen" << std::endl;

  screens.back ().first->on_shutdown ();

  if (screens.back ().second) // delete_screen
    delete_screens.push_back(screens.back ().first);
  
  screens.back () = std::pair<Screen*, bool> (screen, delete_screen);
  screens.back ().first->on_startup ();
}

void
ScreenManager::real_pop_screen ()
{
  std::cout << "XXXXXXXX ScreenManager::pop_screen" << std::endl;

  screens.back ().first->on_shutdown ();

  if (screens.back ().second) // delete_screen
    delete_screens.push_back(screens.back ().first);
  
  std::cout << "ScreenManager::real_pop_screen ()" << std::endl;
  screens.pop_back ();

  if (!screens.empty ())
    {
      screens.back ().first->on_startup ();
    }
}

void
ScreenManager::fade_over (Screen* old_screen, Screen* new_screen)
{
  DeltaManager delta_manager;
  float passed_time = 0;


  std::list<Input::Event*> events;
  while (passed_time < 2.0f)
    {
      float time_delta = delta_manager.getset ();
      passed_time += time_delta;

      int border_x = int((CL_Display::get_width ()/2) * passed_time/2.0f);
      int border_y = int((CL_Display::get_height ()/2) * passed_time/2.0f);

      //std::cout << "FadeOver: " << border_x << " " << border_y << std::endl;

      new_screen->draw ();

      CL_Display::push_clip_rect(CL_ClipRect (0 + border_x, 
					      0 + border_y,
					      CL_Display::get_width () - border_x,
					      CL_Display::get_height () - border_y));
      old_screen->draw ();

      GameDelta delta (time_delta, events);
      new_screen->update (delta);
      old_screen->update (delta);

      CL_Display::pop_clip_rect ();

      Display::flip_display ();
      CL_System::keep_alive ();
    }
}

/* EOF */

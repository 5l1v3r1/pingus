//  $Id: global_event.cxx,v 1.5 2002/06/26 16:49:33 grumbel Exp $
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

#include <stdio.h>
#include <algorithm>
#include <ClanLib/Display/Input/input.h>
#include <ClanLib/Display/Input/keyboard.h>
#include "screenshot.hxx"
#include "console.hxx"
#include "fps_counter.hxx"
#include "global_event.hxx"
#include "globals.hxx"

GlobalEvent global_event;

// FIXME: This belongs into ClanLib
#define PINGUS_CL_KEY_HELP 91

void
GlobalEvent::on_button_press(CL_InputDevice *device, const CL_Key &key)
{
  //  std::cout << "Button pressed..." << std::endl;

  if (device == CL_Input::keyboards[0])
    {
      switch (key.id)
	{
	  // F1 is the general console modifer key...
	case CL_KEY_PAGEUP:
	  if (CL_Keyboard::get_keycode(PINGUS_CL_KEY_HELP))
	    console.increase_lines();
	  break;

	case CL_KEY_PAGEDOWN:
	  if (CL_Keyboard::get_keycode(PINGUS_CL_KEY_HELP))
	    console.decrease_lines();
	  break;

	case CL_KEY_UP:
	  if (CL_Keyboard::get_keycode(PINGUS_CL_KEY_HELP))
	    console.scroll_up();
	  break;

	case CL_KEY_DOWN:
	  if (CL_Keyboard::get_keycode(PINGUS_CL_KEY_HELP))
	    console.scroll_down();	  
	  break;

	case PINGUS_CL_KEY_HELP:
	  console.toggle_display();
	  break; 

	case CL_KEY_F11:
	  fps_counter.toggle_display();
	  console << "Toggling fps counter display" << std::endl;
	  break;

	case CL_KEY_F12:
	  {
	    std::string filename;
	    std::cout << "GlobalEvent::Making screenshot..." << std::endl;
	    filename = Screenshot::make_screenshot();
	    console << "GlobalEvent: Saved screenshot to \"" << filename << "\"" << std::endl;
	    //console << "!\"#$%&'()*+,-./0123456789:;<=>?@";
	    console.newline();
	  }
	  break;

	case CL_KEY_C:
	  draw_collision_map = !draw_collision_map;
	  break;

	case CL_KEY_END:
	  if (CL_Keyboard::get_keycode(CL_KEY_LCTRL) 
	      && CL_Keyboard::get_keycode(CL_KEY_ALT))
	    {
	      puts ("---:: Emergency exit ::---");
	      exit (0);
	    }

	default:
	  // console << "GlobalEvent: Unknown key pressed: " << key.id;
	  break;
	}
    }
}

void
GlobalEvent::on_button_release(CL_InputDevice *device, const CL_Key & /*key*/)
{
  if (device == CL_Input::keyboards[0])
    {
      
    }  
}

/* EOF */

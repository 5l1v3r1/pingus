//  $Id: TimeDisplay.cc,v 1.7 2001/08/04 12:46:22 grumbel Exp $
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

#include <assert.h>
#include <cstdio>

#include "globals.hh"
#include "GameTime.hh"
#include "PingusResource.hh"
#include "TimeDisplay.hh"

TimeDisplay::TimeDisplay()
{
  font = PingusResource::load_font("Fonts/numbers","fonts");
}

void
TimeDisplay::draw()
{
  int time_value = server->get_world()->get_time_left();
  char time_string[256];
  
  if (time_value == -1 && !(pingus_debug_flags & PINGUS_DEBUG_GAMETIME))
    {
      sprintf(time_string, "00");
    }
  else
    {  
      if (!(pingus_debug_flags & PINGUS_DEBUG_GAMETIME))
	{
	  int millisecs = (((time_value * 100)) / game_speed) % 100;
	  int seconds   = (time_value / game_speed % 60);
	  int minutes   = (time_value / (60 * game_speed));
	  char* p;

	  // FIXME: Buffer overflow...
	  sprintf(time_string, "%2d:%2d:%2d", minutes, seconds, millisecs);

	  p = time_string;

	  // Replace any space with a zero
	  while(*p++)
	    {
	      if (*p == ' ')
		*p = '0';
	    }
	}
      else
	{
	  time_value = server->get_world()->get_time_passed();
	  // FIXME: Buffer overflow...
	  sprintf(time_string, "%4d", time_value);
	}
    }
  font->print_right(CL_Display::get_width() - 5, 1, time_string);
}

void
TimeDisplay::set_server(Server* s)
{
  assert(s);
  server = s;
}

/* EOF */

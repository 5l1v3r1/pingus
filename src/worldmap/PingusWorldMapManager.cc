//  $Id: PingusWorldMapManager.cc,v 1.9 2001/03/31 11:21:52 grumbel Exp $
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

#include "../globals.hh"
#include "../algo.hh"
#include "../Display.hh"
#include "PingusWorldMapManager.hh"

PingusWorldMapManager::PingusWorldMapManager ()
{
  is_init = false;
}

PingusWorldMapManager::~PingusWorldMapManager ()
{
}

void 
PingusWorldMapManager::init ()
{
  if (!is_init)
    {
      //sur = PingusResource::load_surface ("volcano", "worldmaps");
      is_init = true;
    }
}

void
PingusWorldMapManager::display ()
{
  on_button_press_slot   = CL_Input::sig_button_press.connect (CL_CreateSlot(this, &PingusWorldMapManager::on_button_press));
  on_button_release_slot = CL_Input::sig_button_release.connect (CL_CreateSlot(this, &PingusWorldMapManager::on_button_release));
  on_mouse_move_slot     = CL_Input::sig_mouse_move.connect (CL_CreateSlot(this, &PingusWorldMapManager::on_mouse_move));

  init ();

  worldmap = new PingusWorldMap (find_file (pingus_datadir, "worldmaps/volcano.xml"));

  worldmap->init ();

  exit_worldmap = false;
  while (!exit_worldmap)
    {
      worldmap->draw ();
      // if (enough_time_passed ())
      worldmap->update ();

      CL_System::keep_alive ();
      Display::flip_display ();
    }
}

void
PingusWorldMapManager::on_mouse_move (CL_InputDevice *, int mouse_x, int mouse_y)
{
  //  std::cout << "mouse: " << mouse_x << " " << mouse_y << std::endl;  
}

void 
PingusWorldMapManager::on_button_press (CL_InputDevice *device, const CL_Key &key)
{
  /*  std::cout << "key press: " << key.id << " " 
	    << CL_Mouse::get_x() << " "
	    << CL_Mouse::get_y() << std::endl;  */

  if (device == CL_Input::keyboards[0])
    {
      switch(key.id)
	{
	case CL_KEY_ESCAPE:
	  exit_worldmap = true;
	  break;
	default:
	  break;
	}
    }
  else
    {
      worldmap->on_button_press (device, key);
    }
}

void 
PingusWorldMapManager::on_button_release (CL_InputDevice *device, const CL_Key &key)
{
  //  std::cout << "key release: " << key.id << std::endl;
}

void
PingusWorldMapManager::on_resize(int w, int h)
{
  std::cout << "Width: " << w << " Height: " << h << std::endl;
}

/* EOF */

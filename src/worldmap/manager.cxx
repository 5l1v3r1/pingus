//  $Id: manager.cxx,v 1.2 2002/06/13 14:25:13 torangan Exp $
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
#include "../path_manager.hxx"
#include "../delta_manager.hxx"
#include "../display.hxx"
#include "worldmap.hxx"
#include "manager.hxx"

using namespace Pingus;
using namespace Pingus::WorldMap;

WorldMapManager* WorldMapManager::current_manager;

WorldMapManager::WorldMapManager ()
{
  current_manager = this;
  is_init = false;
}

WorldMapManager::~WorldMapManager ()
{
}

void 
WorldMapManager::init ()
{
  if (!is_init)
    {
      //sur = PingusResource::load_surface ("volcano", "worldmaps");
      is_init = true;
    }
}

void
WorldMapManager::display ()
{
  on_button_press_slot   = CL_Input::sig_button_press ().connect (this, &WorldMapManager::on_button_press);
  on_button_release_slot = CL_Input::sig_button_release ().connect (this, &WorldMapManager::on_button_release);
  on_mouse_move_slot     = CL_Input::sig_mouse_move ().connect (this, &WorldMapManager::on_mouse_move);

  init ();

  worldmap = boost::shared_ptr<WorldMap::WorldMap>
    (new WorldMap::WorldMap (path_manager.complete("worldmaps/volcano.xml")));

  worldmap->init ();

  exit_worldmap = false;
  DeltaManager delta;
  while (!worldmap->do_exit ())
    {
      worldmap->draw ();
      worldmap->update (delta.getset ());

      if (new_worldmap.get ())
	{
	  worldmap = new_worldmap;
	  new_worldmap = boost::shared_ptr<WorldMap::WorldMap>();
	}

      CL_System::sleep (20);
      CL_System::keep_alive ();
      Display::flip_display ();
    }

  CL_Input::sig_button_press ().disconnect(on_button_press_slot);
  CL_Input::sig_button_release ().disconnect(on_button_release_slot);
  CL_Input::sig_mouse_move ().disconnect(on_mouse_move_slot);
}

void
WorldMapManager::on_mouse_move (CL_InputDevice *, int /*mouse_x*/, int /*mouse_y*/)
{
  //  std::cout << "mouse: " << mouse_x << " " << mouse_y << std::endl;  
}

void 
WorldMapManager::on_button_press (CL_InputDevice *device, const CL_Key &key)
{
  worldmap->on_button_press (device, key);
}

void 
WorldMapManager::on_button_release (CL_InputDevice * /*device*/, const CL_Key & /*key*/)
{
  //  std::cout << "key release: " << key.id << std::endl;
}

void
WorldMapManager::on_resize(int w, int h)
{
  std::cout << "Width: " << w << " Height: " << h << std::endl;
}

void 
WorldMapManager::change_map (std::string filename, int node)
{
  new_worldmap = boost::shared_ptr<WorldMap::WorldMap>
    (new WorldMap::WorldMap (path_manager.complete("worldmaps/" + filename)));
  new_worldmap->set_pingus (node);
}

/* EOF */

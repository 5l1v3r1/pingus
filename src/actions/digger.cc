//  $Id: digger.cc,v 1.22 2001/04/20 20:53:55 grumbel Exp $
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

#include <cstdio>

#include "../World.hh"
#include "../PingusResource.hh"
#include "../PingusSound.hh"
#include "../particles/GroundParticle.hh"
#include "../algo.hh"
#include "digger.hh"

Digger::Digger()
{
}

void
Digger::init(void)
{
  action_name = "Digger";
  environment = (PinguEnvironment)land;

  digger_radius = PingusResource::load_surface ("Other/digger_radius", "pingus");  
  sprite = Sprite (std::string("Pingus/digger") + StringConverter::to_string(pingu->get_owner ()),
		   "pingus");
  digger_c.set_size(4);
  digger_c.set_count(0);

  is_multi_direct = false;
}

void
Digger::update(float delta)
{
  if (++digger_c >= 3)
    {
      dig();
    }

  if (!have_something_to_dig())
    { 
      dig ();
      is_finished = true;
    }
}

bool   
Digger::have_something_to_dig()
{
  if (rel_getpixel(0, -1) != ColMap::NOTHING)
    {
      if (rel_getpixel(0, -1) & ColMap::SOLID)
	{
	  PingusSound::play_wav("chink");
	  return false;  
	}
      else
	return true;
    }
  else
    {
      return false;
    }
}

void
Digger::dig()
{
  pingu->get_world()->get_colmap()->remove(digger_radius, pingu->get_x () - 16, pingu->get_y() - 14);
  pingu->get_world()->get_gfx_map()->remove(digger_radius, pingu->get_x () - 16, pingu->get_y() - 14);
      
  ++pingu->pos.y;
}

/* EOF */

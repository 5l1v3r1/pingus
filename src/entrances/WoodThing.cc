//  $Id: WoodThing.cc,v 1.14 2001/08/10 10:56:14 grumbel Exp $
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

#include <cstdlib>

#include "../World.hh"
#include "../PingusResource.hh"
#include "../particles/SmokeParticle.hh"
#include "../algo.hh"

#include "WoodThing.hh"

WoodThing::WoodThing(EntranceData data)
  : Entrance (data)
{
  pos = data.pos;
  release_rate = data.release_rate;
  last_release = -release_rate;
  direction = data.direction;

  surface  = PingusResource::load_surface("Entrances/woodthing_mov", "entrances");
  surface2 = PingusResource::load_surface("Entrances/woodthing_nmov", "entrances");

  counter.set_size(surface.get_num_frames());
  counter.set_type(GameCounter::once);
  counter.set_speed(2);
  counter =  surface.get_num_frames() - 1;
}

void
WoodThing::update(float delta)
{
  Entrance::update (delta);

  --counter;

  if (rand() % 5 == 0) 
    {
      world->get_particle_holder()
	->add_particle(new SmokeParticle(int(pos.x - (surface.get_width()/2) - 24),
					 int(pos.y - surface.get_height() + 32 - 147),
					 -0.6 * (frand() + 1), -0.6 * (frand() + 1)));
    }
}

void
WoodThing::draw_offset(int x, int y, float s)
{
  if (s == 1.0) 
    {
      surface.put_screen(int(pos.x - (surface.get_width()/2) + x),
			 int(pos.y - surface.get_height() + 32 + y),
			 counter);
    }
  else 
    {
      surface.put_screen((int)((pos.x-32 + x) * s),
			 (int)((pos.y-16 + y) * s),
			 s, s);  
    }
}


/* EOF */

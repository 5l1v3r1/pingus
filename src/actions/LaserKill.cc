//  $Id: LaserKill.cc,v 1.8 2001/04/08 14:10:34 grumbel Exp $
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

#include "../PingusResource.hh"
#include "LaserKill.hh"
#include "../particles/GroundParticle.hh"
#include "../algo.hh"

bool LaserKill::static_surfaces_loaded = false;
CL_Surface LaserKill::static_surface;

LaserKill::LaserKill()
{
}

void
LaserKill::init(void)
{
  action_name = "LaserKill";
  environment = (PinguEnvironment)always;

  if (!static_surfaces_loaded)
    static_surface = PingusResource::load_surface ("Other/laser_kill", "pingus");
  surface = static_surface;

  counter.set_count(0);
  counter.set_size(surface.get_num_frames()/2);
  counter.set_speed(0);
  counter.set_type(Counter::once);

  is_multi_direct = true;
  pingu->set_status(not_catchable);
}

void
LaserKill::update(float delta)
{
  if (counter >= (int)(surface.get_num_frames()) - 1) 
    {
      pingu->set_status(dead);
    }
}

/* EOF */

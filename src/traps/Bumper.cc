//  $Id: Bumper.cc,v 1.16 2001/08/12 18:36:42 grumbel Exp $
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

#include "../World.hh"
#include "../ActionHolder.hh"
#include "../PingusResource.hh"
#include "../PingusSound.hh"
#include "../algo.hh"
#include "../GroundpieceData.hh"
#include "../ColMap.hh"
#include "Bumper.hh"

Bumper::Bumper(const TrapData& data)
{
  pos = data.pos;
  surface = PingusResource::load_surface("Traps/bumper", "traps");
  count = 0;
}

Bumper::~Bumper()
{
}

void
Bumper::update(float delta)
{
  if (upwards) 
    {
      ++count;
      if (count >= (int)surface.get_num_frames())
	{
	  count = 0;
	  upwards = false;
	}
    }
}

void
Bumper::draw_colmap()
{
  std::cout << "Drawing colmap entry" << std::endl;

  CL_SurfaceProvider* prov = CL_SurfaceProvider::load("Traps/bumper_cmap", PingusResource::get("traps"));
  world->get_colmap()->put(prov, (int) pos.x, (int) pos.y, GroundpieceData::GP_SOLID);
}

void 
Bumper::draw_offset(int x, int y, float s)
{
  surface.put_screen(int(pos.x + x), int(pos.y + y), count);
}

void 
Bumper::catch_pingu(boost::shared_ptr<Pingu> pingu)
{
  //  if (!pingu->is_alive())
  //  return;

  if (pingu->get_y() > pos.y + 60 && pingu->get_y() < pos.y + 100)
    {
      if (pingu->get_x() > pos.x + 28 && pingu->get_x() < pos.x + 32)
	{
	  if (!upwards)
	    upwards = true;
	}

      if (upwards && pingu->get_x() > pos.x + 0 && pingu->get_x() < pos.x + 60)
	{
	  pingu->apply_force(CL_Vector((pingu->get_x() - 30)/6, -5));
	}
    }
}

/* EOF */

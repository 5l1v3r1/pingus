//  $Id: basher.cxx,v 1.26 2003/02/19 09:50:36 grumbel Exp $
//
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

#include "../col_map.hxx"
#include "../debug.hxx"
#include "../globals.hxx"
#include "../gui/graphic_context.hxx"
#include "../pingu_map.hxx"
#include "../pingus_resource.hxx"
#include "../pingu.hxx"
#include "../world.hxx"
#include "basher.hxx"

namespace Actions {

Basher::Basher (Pingu* p) 
  : PinguAction(p),
    sprite(PingusResource::load_surface("Pingus/basher0", "pingus")),
    bash_radius(PingusResource::load_surface("Other/bash_radius", "pingus")),
    bash_radius_gfx(PingusResource::load_surface("Other/bash_radius_gfx", "pingus")),
    basher_c(0), 
    first_bash(true)
{
  sprite.set_align_center_bottom();

  bash_radius_width = bash_radius.get_width();
  bash_radius_gfx_width = bash_radius_gfx.get_width();

  // The +1 is just in case bash_radius is an odd no.  In which case, want to
  // round up the result.
  bash_reach = static_cast<int>(bash_radius_width + 1) / 2;

  // Start a bash even so the action will stops instantly after the
  // first bash
  bash();
}

void
Basher::draw (GraphicContext& gc)
{
  if (pingu->direction.is_left())
    sprite.set_direction (Sprite::LEFT);
  else
    sprite.set_direction (Sprite::RIGHT);

  gc.draw (sprite, pingu->get_pos() + Vector (0, +1));
}

void
Basher::update ()
{
  sprite.update ();

  ++basher_c;
  if (basher_c % 3 == 0)
    {
      walk_forward();

      // If on walking forward the Basher has now walked on to water or lava
      if (rel_getpixel(0, -1) == Groundtype::GP_WATER
	  || rel_getpixel(0, -1) == Groundtype::GP_LAVA)
	{
	  pingu->set_action(Actions::Drown);
	}
      // If walking on to something (i.e. hasn't fallen)
      else if (rel_getpixel(0, -1) != Groundtype::GP_NOTHING)
	{
	  // If the Basher has walked into something that it won't be able to
	  // bash
	  if (rel_getpixel(0, 0) == Groundtype::GP_SOLID
	      || rel_getpixel(0, pingu_height) == Groundtype::GP_SOLID)
	    {
	      // Change direction and let walk code walk forward/up to get out.
	      pingu->direction.change();
	      pingu->set_action(Actions::Walker);
	    }
	  else if (have_something_to_dig())
	    {
	      // We only bash every second step, cause the Pingus would
	      // get trapped otherwise in the bashing area.
	      if (basher_c % 2 == 0)
		bash();
	    }
	  else if (sprite.get_progress () > 0.6f) // FIXME: EVIL! 
	    {
	      pingu->set_action(Actions::Walker);
	    }
	}
    }
}

void
Basher::bash()
{
  WorldObj::get_world()->get_colmap()->remove(bash_radius,
					      static_cast<int>(pingu->get_x () - (bash_radius_width / 2)),
					      static_cast<int>(pingu->get_y () - bash_radius_width + 1));
  WorldObj::get_world()->get_gfx_map()->remove(bash_radius_gfx,
					       static_cast<int>(pingu->get_x () - (bash_radius_gfx_width / 2)),
					       static_cast<int>(pingu->get_y () - bash_radius_gfx_width + 1));
}

void
Basher::walk_forward()
{
  int y_inc = 0;

  // Find the correct y position to go to next
  for (y_inc = 0; y_inc >= -max_steps_down; --y_inc)
    {
      // If there is something below, get out of this loop
      if (rel_getpixel(0, y_inc - 1) != Groundtype::GP_NOTHING)
	break;
    }

  if (y_inc < -max_steps_down)
    {
      // The step down is too much.  So stop being a Basher and be a Faller.
      pingu->set_action(Actions::Faller);
    }
  else
    {
      // Note that Pingu::set_pos() is the 'reverse' of the y co-ords of
      // rel_getpixel()
      pingu->set_pos(pingu->get_x() + static_cast<int>(pingu->direction),
                     pingu->get_y() - y_inc);
    }
}

bool
Basher::have_something_to_dig()
{
  if (first_bash)
    {
      first_bash = false;
      return true;
    }

  // Check that there is something "within" the Basher's reach
  for(int x = 0; x <= bash_reach; ++x)
    {
      for (int y = min_bash_height; y <= max_bash_height; ++y)
	{
	  if (rel_getpixel(x, y) == Groundtype::GP_GROUND)
	    {
	      pout(PINGUS_DEBUG_ACTIONS) << "Basher: Found something to dig..." << std::endl;
	      return true;
	    }
	}
    }

  std::cout << "nothing to dig found" << std::endl;
  return false;
}

} // namespace Actions

/* EOF */

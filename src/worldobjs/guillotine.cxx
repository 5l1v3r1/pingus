//  $Id: guillotine.cxx,v 1.11 2003/10/20 13:11:09 grumbel Exp $
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

#include "../display/scene_context.hxx"
#include "../pingu.hxx"
#include "../pingu_holder.hxx"
#include "../world.hxx"
#include "../resource.hxx"
#include "guillotine.hxx"

namespace Pingus {
namespace WorldObjs {

Guillotine::Guillotine(const FileReader& reader)
  : surface  (Resource::load_sprite("traps/guillotinekill")),
    idle_surf(Resource::load_sprite("traps/guillotineidle")),
    killing(false)
{
  reader.read_vector("position", pos);

  counter.set_size(surface.get_frame_count()/2);
  counter.set_type(GameCounter::once);
  counter.set_speed(0.7);
  counter = 0;

  idle_counter.set_size(idle_surf.get_frame_count());
  idle_counter.set_type(GameCounter::loop);
  idle_counter.set_speed(0.3);
  idle_counter = 0;
}

void
Guillotine::draw (SceneContext& gc)
{
  if (killing) {
    if (direction.is_left())
      gc.color().draw(surface, pos, counter);
    else
      gc.color().draw (surface, pos, counter + 12);
  } else {
    gc.color().draw (idle_surf, pos, idle_counter);
  }
}


float
Guillotine::get_z_pos () const
{
  return pos.z;
}

void
Guillotine::update ()
{
  if (counter.finished()) {
    counter = 0;
    killing = false;
  }

  PinguHolder* holder = world->get_pingus();
  for (PinguIter pingu = holder->begin (); pingu != holder->end (); ++pingu)
    catch_pingu(*pingu);

  if (killing) {
    ++counter;
  } else {
    ++idle_counter;
  }
}

void
Guillotine::catch_pingu (Pingu* pingu)
{
  if (!killing)
    {
      if (pingu->is_inside (static_cast<int>(pos.x + 38), static_cast<int>(pos.y + 90),
			    static_cast<int>(pos.x + 42), static_cast<int>(pos.y + 98)))
	{
	  killing = true;
	  pingu->set_status(PS_DEAD);
	  direction = pingu->direction;
	}
    }
}

} // namespace WorldObjs
} // namespace Pingus

/* EOF */

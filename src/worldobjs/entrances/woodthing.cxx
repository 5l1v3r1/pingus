//  $Id: woodthing.cxx,v 1.9 2003/10/20 13:11:09 grumbel Exp $
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

#include "../../math.hxx"
#include "../../gui/graphic_context.hxx"
#include "../../particles/smoke_particle_holder.hxx"
#include "../../resource.hxx"
#include "../../world.hxx"
#include "../../worldobjsdata/entrance_data.hxx"
#include "woodthing.hxx"

namespace Pingus {
namespace WorldObjs {
namespace Entrances {

WoodThing::WoodThing (const WorldObjsData::EntranceData& data_)
  : Entrance(data_)
{
  surface  = Resource::load_sprite("Entrances/woodthing_mov" , "entrances");
  surface2 = Resource::load_sprite("Entrances/woodthing_nmov", "entrances");

  counter.set_size(surface.get_frame_count());
  counter.set_type(GameCounter::once);
  counter.set_speed(2);
  counter = surface.get_frame_count() - 1;
}

void
WoodThing::update ()
{
  Entrance::update ();

  --counter;

  if (rand() % 5 == 0)
    {
      world->get_smoke_particle_holder()->
        add_particle(static_cast<int>(data->pos.x - surface.get_width () /  2 - 24),
                     static_cast<int>(data->pos.y - surface.get_height() + 32 - 147),
                     (Math::frand() + 1) * -0.6f, (Math::frand() + 1) * -0.6f);
    }
}

void
WoodThing::draw (GraphicContext& gc)
{
  gc.draw(surface,
	  Vector(static_cast<int>(data->pos.x - surface.get_width () /  2),
                 static_cast<int>(data->pos.y - surface.get_height() + 32)),
	  (int)counter);
}

} // namespace Entrances
} // namespace WorldObjs
} // namespace Pingus

/* EOF */

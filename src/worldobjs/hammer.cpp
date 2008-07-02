
//  Pingus - A free Lemmings clone
//  Copyright (C) 1999 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "../display/scene_context.hpp"
#include "../pingu.hpp"
#include "../pingu_holder.hpp"
#include "../world.hpp"
#include "../resource.hpp"
#include "hammer.hpp"

namespace WorldObjs {

Hammer::Hammer(const FileReader& reader)
  : sprite(Resource::load_sprite("traps/hammer"))
{
  reader.read_vector("position", pos);
}

float
Hammer::get_z_pos() const
{
  return pos.z;
}

void
Hammer::draw(SceneContext& gc)
{
  gc.color().draw(sprite, pos);
}

void
Hammer::update()
{
  sprite.update();

  if (sprite.is_finished())
    {
      PinguHolder* holder = world->get_pingus();

      for (PinguIter pingu_it = holder->begin (); pingu_it != holder->end (); ++pingu_it)
	{
	  Pingu* pingu = *pingu_it;
	  if (pingu->get_action() != Actions::Splashed)
	    {
	      if (pingu->get_x() > pos.x + 55  && pingu->get_x() < pos.x + 77
		    && pingu->get_y() > pos.y + 146 && pingu->get_y() < pos.y + 185)
		  pingu->set_action(Actions::Splashed);
	    }
	}
      sprite.restart();
    }
}

} // namespace WorldObjs

/* EOF */

//  $Id: exit.cxx,v 1.7 2002/09/16 15:47:35 grumbel Exp $
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

#include "graphic_context.hxx"
#include "col_map.hxx"
#include "world.hxx"
#include "globals.hxx"
#include "exit.hxx"
#include "pingu_holder.hxx"
#include "string_converter.hxx"
#include "pingu_action.hxx"
#include "pingu.hxx"

using namespace Actions;

Exit::Exit(const ExitData& data)
  : sprite (data.desc, 10.0f),
    flag ("misc/flag" + to_string (data.owner_id), "core")
{
  flag.set_align_center_bottom ();
  if (verbose > 2)
    std::cout << "Creating Exit" << std::endl;

  pos  = data.pos;
  desc = data.desc;
  owner_id = data.owner_id;
  use_old_pos_handling = data.use_old_pos_handling;

  sprite.set_align_center_bottom ();

  if (use_old_pos_handling) {
    pos.x = pos.x + (sprite.get_width() / 2);
    pos.y = pos.y + sprite.get_height();
    use_old_pos_handling = false;
  }
}

Exit::~Exit()
{
}

void
Exit::on_startup()
{
  world->get_colmap()->remove(sprite.get_surface (), 
			      int(pos.x) - sprite.get_width ()/2,
			      int(pos.y) - sprite.get_height ());
}

void
Exit::draw (GraphicContext& gc)
{
  gc.draw(sprite, pos);
  gc.draw(flag, pos + CL_Vector (40, 0));
}

///
void
Exit::update (float delta)
{
  sprite.update (delta);

  PinguHolder* holder = world->get_pingu_p ();

  for (PinguIter pingu = holder->begin (); pingu != holder->end (); ++pingu)
    {
      if ((*pingu)->get_x() > pos.x - 1 && (*pingu)->get_x() < pos.x + 1
	  && (*pingu)->get_y() > pos.y - 5 && (*pingu)->get_y() < pos.y + 1)
	{
	  if ((*pingu)->get_status() != PS_EXITED
	      && (*pingu)->get_status() != PS_DEAD
	      && (*pingu)->get_action ()->get_type () != Exiter)
	    {
	      (*pingu)->set_action(Exiter);
	    }
	}
    }
}

/* EOF */

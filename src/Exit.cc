//  $Id: Exit.cc,v 1.24 2001/08/05 21:20:52 grumbel Exp $
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

#include <cassert>

#include "World.hh"
#include "globals.hh"
#include "PingusResource.hh"
#include "Exit.hh"
#include "actions/exiter.hh"
#include "StringConverter.hh"

Exit::Exit(ExitData data)
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

  if (!use_old_pos_handling) {
    sprite.set_align_center_bottom ();
  }
}

Exit::~Exit()
{
}

bool
Exit::catch_pingu(boost::shared_ptr<Pingu> pingu)
{
  float x;
  float y;
  
  if (use_old_pos_handling)
    {
      x = pos.x + (sprite.get_width() / 2);
      y = pos.y + sprite.get_height();
    }
  else
    {
      x = pos.x;
      y = pos.y;
    }

  if (pingu->get_x() > x - 1 && pingu->get_x() < x + 1
      && pingu->get_y() > y - 5 && pingu->get_y() < y + 1)
    {
      if (pingu->get_status() != PS_EXITED
	  && pingu->get_status() != PS_DEAD)
	{
	  pingu->set_action(world->get_action_holder()->get_uaction("exiter"));
	}
      return true;
    }
  return false;
}

void
Exit::draw_colmap()
{
  world->get_colmap()->remove(sprite.get_surface (), 
			      pos.x - sprite.get_width ()/2,
			      pos.y - sprite.get_height ());
}

void
Exit::draw_offset(int x_of, int y_of, float s)
{
  if (s == 1.0) {
    sprite.put_screen(pos.x + x_of, pos.y + y_of);
    if (!use_old_pos_handling)
      flag.put_screen (pos.x + 40 + x_of, pos.y + y_of);
  } else {
    //sprite.put_screen((int)((pos.x + x_of) * s), (int)((pos.y + y_of) * s),
    //s, s);
  }
}

///
void
Exit::update (float delta)
{
  sprite.update (delta);
}

/* EOF */

//  $Id: RocketLauncher.cc,v 1.2 2001/08/02 21:51:03 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#include "../particles/ExplosiveParticle.hh"
#include "../World.hh"
#include "RocketLauncher.hh"

void
RocketLauncher::init()
{
  sprite = Sprite (PingusResource::load_surface 
		   ("Pingus/rocketlauncher" + to_string(pingu->get_owner ()),
		    "pingus"), 10.0f, Sprite::NONE, Sprite::ONCE);
  sprite.set_align_center_bottom ();
  launched = false;

  pingu->get_world ()->get_particle_holder()->add_particle 
    (new ExplosiveParticle (pingu->pos.x, pingu->pos.y - 12, 
			    pingu->direction.is_left() ? -400.0f : 400.0f,
			    0.0f));
}

void
RocketLauncher::update(float delta)
{
  if (sprite.finished ())
    {
      is_finished = true;
    }

  sprite.update (delta);
}

void
RocketLauncher::draw_offset(int x, int y, float s)
{
  if (pingu->direction.is_left ())
    sprite.set_direction (Sprite::LEFT);
  else
    sprite.set_direction (Sprite::RIGHT);
  sprite.put_screen (pingu->pos + CL_Vector (x, y));
}

/* EOF */

//  $Id: laser_kill.cxx,v 1.6 2002/09/13 18:28:26 grumbel Exp $
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

#include "../pingu.hxx"
#include "laser_kill.hxx"

namespace Actions {

LaserKill::LaserKill()
{
}

void
LaserKill::init(void)
{
  sprite = Sprite ("Other/laser_kill", "pingus",
		   20.0f, Sprite::NONE, Sprite::ONCE);
  sprite.set_align_center_bottom ();
}

void 
LaserKill::draw (GraphicContext& gc)
{
  if (pingu->direction.is_left())
    sprite.set_direction (Sprite::LEFT);
  else
    sprite.set_direction (Sprite::RIGHT);

  gc.draw(sprite, pingu->get_pos () - CL_Vector (0, 2));
}

void
LaserKill::update(float delta)
{
  if (sprite.finished ())
    pingu->set_status(PS_DEAD);

  sprite.update (delta);
}

} // namespace Actions

/* EOF */

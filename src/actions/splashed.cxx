//  $Id: splashed.cxx,v 1.16 2003/10/18 23:17:27 grumbel Exp $
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

#include "../vector.hxx"
#include "../gui/graphic_context.hxx"
#include "../world.hxx"
#include "../pingu.hxx"
#include "../worldobj.hxx"
#include "splashed.hxx"

namespace Pingus {
namespace Actions {

Splashed::Splashed (Pingu* p)
  : PinguAction(p),
    particle_thrown(false),
    sound_played(false),
    sprite("pingus/splat", "pingus", 30.0f, Sprite::NONE, Sprite::ONCE)
{
  sprite.set_align_center_bottom();
}

void
Splashed::update ()
{
  sprite.update ();

  if (!particle_thrown)
    {
      particle_thrown = true;
      WorldObj::get_world()->play_sound("splash", pingu->get_pos());
    }

  if (sprite.finished())
    {
      pingu->set_status(PS_DEAD);
    }
}

void
Splashed::draw (GraphicContext& gc)
{
  gc.draw (sprite, pingu->get_pos ());
}

} // namespace Actions
} // namespace Pingus

/* EOF */

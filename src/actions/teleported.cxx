//  $Id: teleported.cxx,v 1.9 2002/10/01 19:53:45 grumbel Exp $
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

#include "../graphic_context.hxx"
#include "../pingu.hxx"
#include "teleported.hxx"

namespace Actions {

Teleported::Teleported(void) : sound_played(false)
{
}

void
Teleported::init(void)
{
  sprite = Sprite ("Pingus/bomber0", "pingus");
}


void 
Teleported::draw (GraphicContext& gc)
{
  gc.draw(sprite, pingu->get_pos ());
}


void
Teleported::update()
{
  pingu->set_pos (x_target, y_target);
  pingu->set_status(PS_ALIVE);
  pingu->set_action(Actions::Walker);
}

} // namespace Actions

/* EOF */

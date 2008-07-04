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
#include "../sprite.hpp"
#include "teleported.hpp"

namespace Actions {

Teleported::Teleported(Pingu* p)
  : PinguAction(p),
    sound_played(false)
{
  sprite = Sprite("pingus/player" + pingu->get_owner_str() + "/bomber");
}


void
Teleported::draw (SceneContext& gc)
{
  gc.color().draw(sprite, pingu->get_pos ());
}


void
Teleported::update()
{
  pingu->set_pos((float)x_target, (float)y_target);
  pingu->set_status(PS_ALIVE);
  pingu->set_action(Actions::Walker);
}

} // namespace Actions

/* EOF */

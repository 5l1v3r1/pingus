//  $Id: angel.cxx,v 1.8 2002/09/04 14:55:12 torangan Exp $
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

#include <math.h>
#include "../pingu.hxx"
#include "../pingus_resource.hxx"
#include "../string_converter.hxx"
#include "angel.hxx"

namespace Actions {

  Angel::Angel () : counter(0.0), x_pos(0)
  {
  }

  void
  Angel::init ()
  {
    x_pos = pingu->get_x();
    counter = 0.0;
    sprite = Sprite (PingusResource::load_surface 
		     ("Pingus/angel" + to_string(pingu->get_owner ()),
		      "pingus"));
    sprite.set_align_center_bottom (); 
  }

  void  
  Angel::update (float delta)
  {
    sprite.update (delta);
    counter += delta;
    pingu->set_pos(x_pos + 20 * sin (counter * 3.0), pingu->get_y() - 50.0f * delta);

    // Out of screen, let the pingu die
    if (pingu->get_y() < -32)
      pingu->set_status (PS_DEAD);
  }

  void   
  Angel::draw_offset (int x_of, int y_of, float s)
  {
    sprite.put_screen (static_cast<int>(pingu->get_x () + x_of),
		       static_cast<int>(pingu->get_y () + y_of));
    UNUSED_ARG(s);
  }

}
/* EOF */

//  $Id: trap.cxx,v 1.2 2002/06/13 14:25:12 torangan Exp $
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

#include "trap.hxx"

Trap::Trap()
{
}

Trap::~Trap()
{
  
}

void 
Trap::draw_offset(int x, int y, float s)
{
  assert(surface);
  //cout << "Count: " << counter.value() << std::endl;
  if (s == 1.0) {
    surface.put_screen((int)pos.x + x, (int)pos.y + y,
		       counter.value());
  } else {
    surface.put_screen((int)((pos.x + x) * s), 
		       (int)((pos.y + y) * s),
		       s, s, counter.value());
  }
}

void 
Trap::update(float delta)
{
 if (delta); // do nothing
}

/* EOF */

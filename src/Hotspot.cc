//  $Id: Hotspot.cc,v 1.1 2000/02/04 23:45:18 mbn Exp $
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

#include <cstdio>
#include <iostream>

#include "Hotspot.hh"
#include "globals.hh"
#include "PLF.hh"
#include "PingusResource.hh"

Hotspot::Hotspot(hotspot_data spot)
{
  if (verbose > 2)
    cout << "Creating Hotspot" << endl;

  x_pos = spot.x_pos;
  y_pos = spot.y_pos;
  z_pos = spot.z_pos;
  para  = spot.para;
  speed = spot.speed;

  surface = CL_Surface::load(spot.desc.res_name.c_str(), 
			     PingusResource::get(spot.desc.filename));
  
  if (speed != -1)
    {
      count.set_size(surface->get_num_frames());
      count.set_speed(speed);
      count = 0;
    }
}

void 
Hotspot::draw_offset(int x, int y, float s)
{
  /*
  cout << "Hotspot: " 
       << x << " : "
       << y << " : "
       << x_pos << " : "
       << y_pos << " : " 
       << para << " : " 
       << endl;
*/  
  if (s == 1.0)
    {
      surface->put_screen((int)((x_pos + x) * para), (int)((y_pos + y) * para),
			  (int)count);
    }
  else 
    {
      surface->put_screen((int)((x_pos + x) * s * para), (int)((y_pos + y) * s * para),
			  s, s, (int)count);      
    }

  ++count;
}

/* EOF */

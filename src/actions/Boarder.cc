//  $Id: Boarder.cc,v 1.1 2001/07/22 12:47:00 grumbel Exp $
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

#include "../PingusResource.hh"
#include "Boarder.hh"

Boarder::Boarder ()
{
}

void
Boarder::init()
{
  x_pos = pingu->pos.x;
  speed = 0.0;
  action_name = "Boarder";
  environment = (PinguEnvironment)land;
  sprite = Sprite (PingusResource::load_surface 
		   ("Pingus/boarder" + to_string(pingu->get_owner ()),
		    "pingus"));
  sprite.set_align_center_bottom (); 
}

void  
Boarder::update(float delta)
{
  if (pingu->direction.is_left ())
    sprite.set_direction(Sprite::LEFT); 
  else
    sprite.set_direction(Sprite::RIGHT); 
  sprite.update (delta);

  if (on_ground ())
    {
      if (speed < 15.0)
	speed += 15.0 * delta;
      else {
	//std::cout << "MAXSPEED REACHED: " << pingu->direction * speed << std::endl;
	speed = 15.0;
      }
      
      // Incremental update so that we don't skip pixels
      double new_x_pos = pingu->pos.x + pingu->direction * speed;
      while (int(new_x_pos) != int(pingu->pos.x) && !is_finished)
	{
	  double old_pos = pingu->pos.x;
	  pingu->pos.x += (int(pingu->pos.x) < int(new_x_pos)) ? 1 : -1;
	  
	  if (pingu->rel_getpixel (1, 0))
	    {
	      // Hit a wall
	      pingu->pos.x = old_pos;// + (pingu->direction * 10);
	      ////pingu->pos.y = 10;

	      pingu->direction.change ();
	      is_finished = true;
	      pingu->apply_force (CL_Vector(speed * pingu->direction * 0.5,
					    -speed * abs(pingu->direction) * 0.5));
	    }
	}
    }
  else
    {
      is_finished = true;
      pingu->apply_force (CL_Vector(speed * pingu->direction, 0));
    }
}

void   
Boarder::draw_offset(int x_of, int y_of, float s)
{
  sprite.put_screen (pingu->get_x () + x_of,
		     pingu->get_y () + y_of);
}

bool
Boarder::on_ground ()
{
  return pingu->rel_getpixel (0, -1) || pingu->rel_getpixel (0, -2);
}

/* EOF */

//  $Id: view.cxx,v 1.2 2002/06/13 14:25:12 torangan Exp $
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

#include <ClanLib/Display/Display/display.h>
#include "mouse_controller.hxx"
#include "view.hxx"
#include "world.hxx"

// static variables
World* View::world;

View::View(int x1, int y1, int x2, int y2, float s)
  : current_pingu (0),
    controller (new MouseController ()) 
{
  assert(world);

  size = s;

  clip_rect = CL_ClipRect(x1, y1, x2 + 1, y2 + 1);

  x1_pos = x1;
  y1_pos = y1;

  x2_pos = x2;
  y2_pos = y2;
  
  x_offset = 0;
  y_offset = 0;

  make_range();
}

View::~View()
{
  //FIXME: This is dangerous and might cause throuble when the code is reordered
  delete controller;
}

void
View::draw()
{
  assert(world);
  float color;

  if (is_over(controller->get_x(), controller->get_y()))
    {
      color = 1.0;
      mouse_over = true;
    } 
  else 
    {
      color = 0.0;
      mouse_over = false;
    }

  CL_Display::push_clip_rect();
  CL_Display::set_clip_rect(clip_rect);

  // Drawing the world
  world->draw(x1_pos, y1_pos,
	      x2_pos - x1_pos + 1, y2_pos - y1_pos + 1,
	      x_offset, y_offset, size);
  
  cap.set_pingu(current_pingu);
  cap.draw_offset(get_x_pos() + get_x_offset(), 
		  get_y_pos() + get_y_offset(),
		  size);
  
  CL_Display::pop_clip_rect();
}

void
View::set_world(World* w)
{
  world = w;
}

bool
View::is_over(int x, int y)
{
  if (x >= x1_pos && x <= x2_pos 
      && y >= y1_pos && y <= y2_pos) {
    return true;
  } else {
    return false;
  }
}

bool
View::is_current()
{
  return mouse_over;
}

int
View::get_x_offset() const
{
  return (int)x_offset;
}

int
View::get_y_offset() const
{
  return (int)y_offset;
}

void
View::set_x_offset(int x)
{
  x_offset = x;
}

void
View::set_y_offset(int y)
{
  y_offset = y;
}

void
View::shift_x_offset(int dx)
{
  x_offset += dx;
}

void
View::shift_y_offset(int dy)
{
  y_offset += dy;
}

int
View::get_x_pos() const
{
  return x1_pos;
}

int
View::get_y_pos() const
{
  return y1_pos;
}

void
View::set_zoom(double s)
{
  size = s;
  make_range();
}

void
View::make_range()
{
  // Bug: this works not very good
  x_offset.set_range(0, (int)(x2_pos - x1_pos - (world->get_width()  * size)));
  y_offset.set_range(0, (int)(y2_pos - y1_pos - (world->get_height() * size)));
}

double
View::get_zoom(void)
{
  return size;
}

void 
View::set_pingu(Pingu* p)
{
  current_pingu = p;
}

CL_Vector 
View::get_center ()
{
  return CL_Vector (-x_offset + get_width ()/2, -y_offset + get_height ()/2);
}

/* EOF */

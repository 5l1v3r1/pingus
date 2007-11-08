//  $Id$
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2007 Ingo Ruhnke <grumbel@gmx.de>
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

#include "globals.hpp"
#include "fonts.hpp"
#include "display/drawing_context.hpp"
#include "slider_box.hpp"

SliderBox::SliderBox(const Rect& rect)
  : RectComponent(rect),
    value(10),
    drag_drop(false)
{
}

void
SliderBox::draw(DrawingContext& gc)
{
  if (maintainer_mode)
    gc.draw_rect(rect, Color(0, 255, 255));

  if (value == 0)
    {
      gc.print_center(Fonts::chalk_normal, rect.left + rect.get_width()/2, rect.top, "off");
    }
  else
    {
      for(int i = 0; i < 20; ++i)
        {
          if (i < value)
            gc.print_left(Fonts::chalk_normal, rect.left + i*(rect.get_width()-12)/20 + 6, rect.top, "l");
          //gc.print_left(Fonts::chalk_normal, rect.left + i*(rect.get_width()-12)/20 + 6, rect.top, "l");
        }
    }
  
  gc.print_left(Fonts::chalk_normal, rect.left, rect.top, 
                "[");
  gc.print_right(Fonts::chalk_normal, rect.right, rect.top, 
                 "]");
}

void
SliderBox::on_primary_button_press(int x, int y)
{
  drag_drop = true;
  on_pointer_move(x, y);
}

void
SliderBox::on_primary_button_release(int x, int y)
{
  drag_drop = false;
  on_pointer_move(x, y);
}

void
SliderBox::on_pointer_move(int x, int y)
{
  if (drag_drop)
    {
      x -= rect.left;
  
      value = 20 * x / (rect.get_width() - 12);
  
      if (value > 20)
        value = 20;
      else if (value < 0)
        value = 0; 
    }
}

/* EOF */

//  $Id: FadeOut.cc,v 1.4 2000/02/15 13:09:50 grumbel Exp $
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

#include <ClanLib/core.h>

#include "FadeOut.hh"
#include "globals.hh"

void
FadeOut::random(void)
{
  if (maintainer_mode) {
    CL_Display::clear_display();    
  } else {
    switch(rand() % 2) {
    case 0:
      if (verbose) std::cout << "FadeOut::black_rect" << std::endl;
      black_rect();
      break;
    case 1:
      if (verbose) std::cout << "FadeOut::fade_to_black" << std::endl;
      fade_to_black();
      break;
    case 2:
      CL_Display::clear_display();
      if (verbose) std::cout << "FadeOut::clear_display()" << std::endl;    
      break;
    default:
      black_rect();
      break;
    }
  }
}

void
FadeOut::black_rect(int steps)
{
  int x1, x2, y1, y2;
  double step_w = (CL_Display::get_width()  / 2.0) / steps;
  double step_h = (CL_Display::get_height() / 2.0) / steps ;

  CL_Display::sync_buffers();

  for(int i=0; i <= steps; ++i) 
    {
      x1 = (int)((CL_Display::get_width()  / 2) - (step_w * i));
      y1 = (int)((CL_Display::get_height() / 2) - (step_h * i));
      x2 = (int)((CL_Display::get_width()  / 2) + (step_w * i));
      y2 = (int)((CL_Display::get_height() / 2) + (step_h * i));
      
      CL_Display::fill_rect(x1, y1, x2, y2, 0.0, 0.0, 0.0, 1.0);
      CL_System::sleep(10);
      CL_Display::flip_display(true);
    }  
  clear();
}

void
FadeOut::fade_to_black(int steps)
{
  CL_Display::sync_buffers();

  for(int i = 0; i < steps; i++)
    {
      CL_Display::fill_rect(0,0,
			    CL_Display::get_width(),
			    CL_Display::get_height(),
			    0.0, 0.0, 0.0,
			    ((double)i)/steps);

      CL_Display::flip_display(true);
    }
}

void
FadeOut::clear(void)
{
  CL_Display::clear_display();
  CL_Display::flip_display();
  CL_Display::sync_buffers();
}

/* EOF */

//  $Id: fade_out.cxx,v 1.11 2003/10/21 11:01:52 grumbel Exp $
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

#include <iostream>
#include <ClanLib/Core/System/system.h>
#include <ClanLib/Display/display.h>
#include "gui/display.hxx"
#include "fade_out.hxx"
#include "globals.hxx"
#include "math.hxx"

namespace Pingus {

FadeOut::FadeOut (float seconds, CL_Colorf color_)
  : complete_time(seconds), passed_time(0),
    color(color_)
{
}

FadeOut::~FadeOut ()
{
}

void
FadeOut::reset ()
{
  passed_time = 0;
}

void
FadeOut::update (float delta)
{
  passed_time += delta;
}

void
FadeOut::set_progress (float /*progress*/)
{

}

bool
FadeOut::finished ()
{
  if (get_progress () >= 1.0f)
    return true;
  else
    return false;
}

float
FadeOut::get_progress ()
{
	return Math::min(passed_time/complete_time, 1.0f);
}

void
FadeOut::random (void)
{
  if (maintainer_mode) {
    CL_Display::clear();
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
      CL_Display::clear();
      if (verbose) std::cout << "FadeOut::clear_display()" << std::endl;
      break;
    default:
      black_rect();
      break;
    }
  }
}

void
FadeOut::black_rect (int steps)
{
  int x1, x2, y1, y2;
  double step_w = (CL_Display::get_width()  / 2.0) / steps;
  double step_h = (CL_Display::get_height() / 2.0) / steps ;

#ifdef CLANLIB_0_6
  CL_Display::sync_buffers();
#endif

  for(int i=0; i <= steps; ++i)
    {
      x1 = static_cast<int>((CL_Display::get_width()  / 2) - (step_w * i));
      y1 = static_cast<int>((CL_Display::get_height() / 2) - (step_h * i));
      x2 = static_cast<int>((CL_Display::get_width()  / 2) + (step_w * i));
      y2 = static_cast<int>((CL_Display::get_height() / 2) + (step_h * i));

      CL_Display::fill_rect(CL_Rect(x1, y1, x2, y2),
                            Display::to_color(0.0, 0.0, 0.0, 1.0));
      CL_System::sleep(0);
      Display::flip_display(true);
    }
  clear();
}

void
FadeOut::fade_to_black (int steps)
{
#ifdef CLANLIB_0_6
  CL_Display::sync_buffers();
#endif

  for(int i = 0; i < steps; ++i)
    {
      CL_Display::fill_rect(CL_Rect(0, 0,
                                    CL_Display::get_width(),
                                    CL_Display::get_height()),
			    Display::to_color(0.0f, 0.0f, 0.0f,
                                              static_cast<float>(i)/steps));

      Display::flip_display(true);
    }
}

void
FadeOut::clear (void)
{
  CL_Display::clear();
  Display::flip_display();
#ifdef CLANLIB_0_6
  CL_Display::sync_buffers();
#endif
}

void
EnlargingRectFadeOut::draw ()
{
  //std::cout << "EnlargingRectFadeOut:: draw" << std::endl;
  int width = int(CL_Display::get_width () * get_progress ());
  CL_Display::fill_rect (CL_Rect(0, 0, width, CL_Display::get_height ()),
			 Display::to_color(color.red,  color.green, color.blue, 1.0f));
}

} // namespace Pingus

/* EOF */

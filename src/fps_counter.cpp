//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#include <stdio.h>
#include "fonts.hpp"
#include "fps_counter.hpp"
#include "gettext.h"
#include "display/display.hpp"

FPSCounter fps_counter;

FPSCounter::FPSCounter()
{
  start_time = SDL_GetTicks();
  strcat(fps_string, "");
  fps_count = 0;
}

FPSCounter::~FPSCounter()
{
}

void
FPSCounter::draw()
{
  update_fps_counter();

  if (odd_frame)
    {
      Fonts::pingus_small.draw(origin_center, Display::get_width()/2, 34, fps_string);
      odd_frame = false;
    }
  else
    {
      Fonts::pingus_small.draw(origin_center, Display::get_width()/2, 34, "+ " + std::string(fps_string) + " +");
      odd_frame = true;
    }
}

void
FPSCounter::update_fps_counter()
{
  unsigned int current_time = SDL_GetTicks();
  int current_fps;

  fps_count++;

  if (start_time + 1000 < current_time)
    {
      current_fps = fps_count * 1000 / (current_time - start_time);
      snprintf(fps_string, 16, "%d fps", current_fps);
      fps_count = 0;
      start_time = SDL_GetTicks();
    }
}


/* EOF */

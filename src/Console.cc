//  $Id: Console.cc,v 1.3 2000/06/14 14:57:54 grumbel Exp $
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

#include <algorithm>
#include <cstdio>
#include "PingusResource.hh"
#include "Console.hh"

// Globale console
Console console;

Console::Console()
{
  is_init = false;
  is_visible = false;
  current_pos = 0;
  number_of_lines = 10;
}

Console::~Console()
{
}

// We are not initialising the console in the constructor, 'cause
// that doesn't work (ClanLib hasn't init the display at that point) void
void
Console::init()
{
  std::cout << "Console: Init..." << std::endl;
  font = CL_Font::load("Fonts/xterm", PingusResource::get("fonts.dat"));
  //*this << "Console V0.2" << std::endl;
  this->println("! \" #  $ %% 0 123 <=>");
  is_init = true;
}

void
Console::draw()
{
  assert(is_init);

  int start_y_pos = 
    CL_Display::get_height() - (font->get_height() * (number_of_lines + 3));
  bool draw_current_line = current_line.empty();
  int start_index;

  if (draw_current_line)
    start_index =  max(0, current_pos - number_of_lines);
  else
    start_index =  max(0, current_pos - number_of_lines-1);

  CL_Display::fill_rect(0, start_y_pos,
			CL_Display::get_width(),
			CL_Display::get_height(),
			0.0, 0.0, 0.0, 0.5);

  for(unsigned int i = start_index, j=1; 
      i < output_buffer.size(); 
      i++, j++)
    {
      font->print_left(10, 
		       start_y_pos + j * font->get_height(), 
		       output_buffer[i].c_str());
    }
  if (draw_current_line)
    font->print_left(10, start_y_pos + (number_of_lines + 1) * font->get_height(),
		     current_line.c_str());
}

void
Console::print(char* format, ...) 
{
  char str_buffer[128];
  va_list argp;

  va_start(argp, format);
  vsnprintf(str_buffer, 128, format, argp);
  va_end(argp);

  output_buffer.push_back(str_buffer);
  current_pos++;
}

void
Console::println(char* format, ...)
{
  char str_buffer[128];
  va_list argp;

  va_start(argp, format);
  vsnprintf(str_buffer, 128, format, argp);
  va_end(argp);

  output_buffer.push_back(str_buffer);
  current_pos++;
  newline();
}

void
Console::newline()
{
  output_buffer.push_back(current_line);
  current_pos++;
  current_line = "";
}

Console& 
Console::operator<<(string str)
{
  output_buffer.push_back(str);
  current_pos++;
  std::cout << str << std::endl;
  return *this;
}

Console&
Console::operator<<(int)
{
  return *this;
}

void
Console::on_event()
{
  draw();
}

/* EOF */

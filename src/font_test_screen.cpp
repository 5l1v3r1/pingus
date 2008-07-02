//  $Id: font_test_screen.cpp 3623 2008-07-02 17:59:58Z grumbel $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2007 Ingo Ruhnke <grumbel@gmx.de>
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

#include <iostream>

#include "input/event.hpp"
#include "fonts.hpp"
#include "string_util.hpp"
#include "display/drawing_context.hpp"
#include "font_description.hpp"
#include "font_test_screen.hpp"

FontTestScreen::FontTestScreen(const Pathname& fontfile)
  : scrollx(0),
    scrolly(0),
    dark(true)
{
  std::cout << "### Loading font file: " << fontfile << std::endl;
  font = Font(FontDescription(fontfile));
  reference = Font(FontDescription(Pathname("images/fonts/reference-iso-8859-1.font", Pathname::DATA_PATH)));
}

bool
FontTestScreen::draw(DrawingContext& gc)
{
  int checker = 40;
  for(int y = 0; y < gc.get_height()/checker; y += 1)
    for(int x = 0; x < gc.get_width()/checker; x += 1)
      {
        if ((x+y) % 2 != 0)
          gc.draw_fillrect(x*checker, y*checker,
                           x*checker + checker, y*checker + checker,
                           dark ? Color(50, 50, 50) : Color(255, 255, 255));
        else
          gc.draw_fillrect(x*checker, y*checker,
                           x*checker + checker, y*checker + checker,
                           dark ? Color(0, 0, 0) : Color(200,200,200));
      }

  gc.print_left(Fonts::chalk_large, 10, 10, "Pingus - Font Test");

  gc.push_modelview();
  gc.translate(scrollx, scrolly);

  for(int i = 0; i < 256; ++i)
    {
      int x = 64 + (i%20)*(font.get_height() + 24);
      int y = 64 + (i/20)*(font.get_height() + reference.get_height()*3);

      // print the actual character
      gc.print_left(reference,
		    x,
		    y - reference.get_height(),
                    std::string(1, char(i)));
      // print the index number
      gc.print_left(reference,
		    x, 
		    y + font.get_height(),
		    StringUtil::to_string(i));
      
      if (font.get_width(char(i)))
        {
          gc.draw_rect(x, y, 
                       x+font.get_height(), 
                       y+font.get_height(), 
                       Color(0,0,255));
          gc.draw_rect(x, y, 
                       x+font.get_width(char(i)), 
                       y+font.get_height(), 
                       Color(255,0,255));
          gc.print_left(font,
                        x, y,
                        std::string(1, char(i)));
        }
      else
        {
          gc.draw_rect(x, y, 
                       x+font.get_height(), 
                       y+font.get_height(), 
                       Color(255,0,0));
        }
    }
  gc.pop_modelview();

  return true;
}

void
FontTestScreen::update(const Input::Event& event)
{
  switch (event.type)
    {
      case Input::BUTTON_EVENT_TYPE:
        if (event.button.state == Input::BUTTON_PRESSED &&
            event.button.name == Input::PRIMARY_BUTTON)
          dark = !dark;
        break;
            
      case Input::SCROLLER_EVENT_TYPE:
        scrollx += event.scroll.x_delta;
        scrolly += event.scroll.y_delta;
        break;
          
      default:
        break;
    }
} 

/* EOF */

//  $Id: Credits.cc,v 1.3 2000/03/12 02:07:27 grumbel Exp $
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

#include "PingusResource.hh"
#include "Credits.hh"

Credits::Credits()
{  
  surface = CL_Surface::load("Game/pingubw", PingusResource::get("game.dat"));
  font = CL_Font::load("Fonts/pingus", PingusResource::get("fonts.dat"));
  font_small = CL_Font::load("Fonts/pingus_small", PingusResource::get("fonts.dat"));

  // The credits vector holds the strings to display. The first
  // character of each string is a special character, which indicates
  // the size of the font or other special stuff. "-" means large
  // font, "_" is a small font and "n" means a newline.

  credits.push_back("_If I forgot somebody in this");
  credits.push_back("_list, just drop me a line and");
  credits.push_back("_I'll fix this.");
  credits.push_back("n");

  credits.push_back("-Programming");
  credits.push_back("_Ingo Ruhnke");
  credits.push_back("_Michael K\"aser");
  credits.push_back("_Peter Todd");
  credits.push_back("n");

  credits.push_back("-Gfx");
  credits.push_back("_Stefan Stiasny");
  credits.push_back("_Alan Tennent");
  credits.push_back("_Craig Timpany");
  credits.push_back("_Joel Fauche");
  credits.push_back("_Michael Mestre");
  credits.push_back("n");

  credits.push_back("-Music");
  credits.push_back("_H. Matthew Smith"); 
  credits.push_back("_Joseph Toscano");
  credits.push_back("n");

  credits.push_back("-Special");
  credits.push_back("-Thanks to");
  credits.push_back("_Jules Bean");
  credits.push_back("_David Philippi");
  credits.push_back("_Kenneth Gangst�");
  credits.push_back("_Johnny Taporg");
  credits.push_back("_Werner Steiner");
  credits.push_back("_Kenneth Gangst�");
  credits.push_back("_Tuomas (Tigert) Kuosmanen");
  credits.push_back("_Keir Fraser");  

  credits.push_back("n");

}

Credits::~Credits()
{
  
}

// FIXME: We have no time handling here, so it might run to fast on
// fast computers
void
Credits::display()
{
  int x;
  int y;
  int yof;
  bool quit = false;
  cout << "Credits::display()" << endl;

  y = CL_Display::get_height() + 50;
  x = CL_Display::get_width() * 3 / 4;

  while(!quit)
    {
      y -= 1;
      CL_Display::clear_display(1.0, 1.0, 1.0);
      
      surface->put_screen((CL_Display::get_width() / 4) - (surface->get_width() / 2),
			  (CL_Display::get_height() / 2) - (surface->get_height() / 2));

      CL_Display::fill_rect(CL_Display::get_width() / 2, 0,
			    CL_Display::get_width(), CL_Display::get_height(),
			    0.0, 0.0, 0.0, 1.0);

      yof = 0;
      for (vector<string>::iterator i = credits.begin(); i != credits.end(); i++)
	{
	  switch ((*i)[0])
	    {
	    case '-':
	      font->print_center(x, y + yof, i->substr(1).c_str());
	      yof += font->get_height() + 5;
	      break;
	    case '_':
	      font_small->print_center(x, y + yof, i->substr(1).c_str());
	      yof += font_small->get_height() + 5;
	      break;
	    case 'n':
	      yof += 50;
	      break;
	    default:
	      cout << "Credits: Syntax error" << endl;
	      break;
	    }
	}
      if (y + yof < -50)
	quit = true;  

      CL_Display::flip_display();  
     
      CL_System::keep_alive();

      if (CL_Keyboard::get_keycode(CL_KEY_SPACE))
	y -= 10;
	
      if (CL_Keyboard::get_keycode(CL_KEY_ESCAPE))
	quit = true;
    }

  cout << "Credits: done" << endl;
}

/* EOF */

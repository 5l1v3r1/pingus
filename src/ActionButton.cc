//  $Id: ActionButton.cc,v 1.1 2000/02/04 23:45:18 mbn Exp $
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


#include "globals.hh"
#include "PingusResource.hh"
#include "ActionButton.hh"

Button::Button()
{
}

Button::~Button()
{
}

EventButton::EventButton(int x, int y, string str)
{
  surface = CL_Surface::load(str.c_str(), PingusResource::get("global.dat"));
  x_pos = x;
  y_pos = y;
}

void
EventButton::draw()
{
  if (mouse_over()) {
    CL_Display::fill_rect(x_pos, y_pos, 
			  x_pos + surface->get_width(), y_pos + surface->get_height(),
			  1.0, 1.0, 1.0, 1.0);
  }
  surface->put_screen(x_pos, y_pos);
}

bool
EventButton::mouse_over()
{
  if (CL_Mouse::get_x() > x_pos && CL_Mouse::get_x() < x_pos + int(surface->get_width())
      && CL_Mouse::get_y() > y_pos && CL_Mouse::get_y() < y_pos + int(surface->get_height()))
    {
      return true;
    }
  else 
    {
      return false;
    }
}

ActionButton::ActionButton()
{
}

ActionButton::~ActionButton()
{
}

void
ActionButton::init(int x, int y, string str)
{
  //  make_action = func;
  x_pos = x;
  y_pos = y;
  name = str;
 
  font = CL_Font::load("Fonts/courier_small",PingusResource::get("fonts.dat"));
  font_h = CL_Font::load("Fonts/smallfont", PingusResource::get("fonts.dat"));

  if (str != "empty") {
    surface   = CL_Surface::load(("Pingus/" + str).c_str(),
				    PingusResource::get("pingus.dat"));
    action_c.set_size(surface->get_num_frames());
    action_c.set_speed(50);
  } else {
    surface = 0;
  }
}

bool
ActionButton::is_pressed()
{
  return false;
}

void
ActionButton::let_move()
{
  ++action_c;
}

string
ActionButton::get_action_name()
{
  return name;
}

void
ActionButton::set_action_holder(ActionHolder* h)
{
  action_holder = h;
}


HorizontalActionButton::HorizontalActionButton(int x, int y, string str)
{
  init(x, y, str);  
}

HorizontalActionButton::~HorizontalActionButton()
{
}

bool
HorizontalActionButton::mouse_over()
{
  if (CL_Mouse::get_x() > x_pos && CL_Mouse::get_x() <= x_pos + 37
      && CL_Mouse::get_y() > y_pos && CL_Mouse::get_y() < y_pos + 55) 
    {
      return true;
    } 
  else 
    {
      return false;
    }
}

// HorizontalActionButton
void
HorizontalActionButton::draw()
{
  char str[256];
  // FIXME: This could need some optimization, throwing strings all
  // around, doesn't look like a good idea. 
  available = action_holder->get_available(name);

  if (unlimited_actions) {
    sprintf(str, "oo");
  } else {
    sprintf(str, "%d", available);
  }

  if (pressed) 
    {
      if (fast_mode) {
	CL_Display::fill_rect(x_pos + 1, y_pos, x_pos + 37, y_pos + 55 ,
			      1.0, 1.0, 1.0, 1.0);
      } else {
	CL_Display::fill_rect(x_pos + 1, y_pos, x_pos + 37, y_pos + 55 ,
			      1.0, 1.0, 1.0, 0.5);
      }
      font_h->print_center(x_pos + 25, y_pos + 5, str);
    }
  else
    {
      if (fast_mode) {
	// do nothing
      } else {
	CL_Display::fill_rect(x_pos + 1, y_pos, x_pos + 37, y_pos + 55 ,
			      0.4, 0.4, 0.4, 0.5);
      }
      font->print_center(x_pos + 25, y_pos + 5, str);
    }
  surface->put_screen(x_pos + 3, y_pos + 20, action_c);
}

VerticalActionButton::VerticalActionButton(int x, int y, string str)
{
  init(x, y, str);
}

VerticalActionButton::~VerticalActionButton()
{
}

bool
VerticalActionButton::mouse_over()
{
  if (CL_Mouse::get_x() > x_pos && CL_Mouse::get_x() < x_pos + 60
      && CL_Mouse::get_y() > y_pos && CL_Mouse::get_y() <= y_pos + 35) 
    {
      return true;
    } 
  else 
    {
      return false;
    }
}

void
VerticalActionButton::draw()
{
  char str[256];
  // FIXME: This could need some optimization, throwing strings all
  // around, doesn't look like a good idea. 
  available = action_holder->get_available(name);

  if (unlimited_actions) {
    sprintf(str, "oo");
  } else {
    sprintf(str, "%d", available);
  }

  if (pressed) 
    {
      if (fast_mode) {
	CL_Display::fill_rect(x_pos, y_pos, x_pos + 60, y_pos + 35 ,
			      1.0, 1.0, 1.0, 1.0);
      } else {
	CL_Display::fill_rect(x_pos, y_pos, x_pos + 60, y_pos + 35 ,
			      1.0, 1.0, 1.0, 0.5);
      }
      font_h->print_center(x_pos + 50, y_pos + 16, str);
    }
  else
    {
      if (fast_mode) {
	// do nothing
      } else {
	CL_Display::fill_rect(x_pos + 1, y_pos, x_pos + 60, y_pos + 35 ,
			      0.4, 0.4, 0.4, 0.5);
      }
      font->print_center(x_pos + 50, y_pos + 16, str);
    }
  surface->put_screen(x_pos + 3, y_pos + 1, action_c);
}

ArmageddonButton::ArmageddonButton(int x, int y)
{
  surface = CL_Surface::load("Buttons/armageddon_anim", PingusResource::get("global.dat"));
  counter.set_size(surface->get_num_frames());
  x_pos = x;
  y_pos = y;
}

void
ArmageddonButton::draw()
{
  // FIXME
  if (false)
    {
      CL_Display::fill_rect(x_pos, y_pos, 
			    x_pos + surface->get_width(), y_pos + surface->get_height(),
			    1.0, 1.0, 1.0, 1.0);
      surface->put_screen(x_pos, y_pos, ++counter);
    } 
  else 
    {
      surface->put_screen(x_pos, y_pos, 7);
    }
}

bool
ArmageddonButton::mouse_over()
{
  if (CL_Mouse::get_x() > x_pos && CL_Mouse::get_x() < x_pos + int(surface->get_width())
      && CL_Mouse::get_y() > y_pos && CL_Mouse::get_y() < y_pos + int(surface->get_height()))
    {
      return true;
    } else  {
      return false;
    } 
}

ForwardButton::ForwardButton(int x, int y)
{
  surface = CL_Surface::load("Buttons/forward", PingusResource::get("global.dat"));
  x_pos = x;
  y_pos = y;
}

void
ForwardButton::draw()
{
  if (server->get_fast_forward())
    {
      CL_Display::fill_rect(x_pos, y_pos, 
			    x_pos + surface->get_width(), y_pos + surface->get_height(),
			    1.0, 1.0, 1.0, 1.0);
    }
  surface->put_screen(x_pos, y_pos);
}

bool
ForwardButton::mouse_over()
{
  if (CL_Mouse::get_x() > x_pos && CL_Mouse::get_x() < x_pos + int(surface->get_width())
      && CL_Mouse::get_y() > y_pos && CL_Mouse::get_y() < y_pos + int(surface->get_height()))
    {
      return true;
    } else  {
      return false;
    } 
}

PauseButton::PauseButton(int x, int y)
{
  surface = CL_Surface::load("Buttons/pause", PingusResource::get("global.dat"));
  x_pos = x;
  y_pos = y;
}

void
PauseButton::draw()
{
  if (server->get_pause()) 
    {
      CL_Display::fill_rect(x_pos, y_pos, 
			    x_pos + surface->get_width(), y_pos + surface->get_height(),
			    1.0, 1.0, 1.0, 1.0);
    }
  surface->put_screen(x_pos, y_pos);
}

bool
PauseButton::mouse_over()
{
  if (CL_Mouse::get_x() > x_pos && CL_Mouse::get_x() < x_pos + int(surface->get_width())
      && CL_Mouse::get_y() > y_pos && CL_Mouse::get_y() < y_pos + int(surface->get_height()))
    {
      return true;
    } else  {
      return false;
    } 
}

/* EOF */

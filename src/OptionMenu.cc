//  $Id: OptionMenu.cc,v 1.24 2000/07/10 18:42:25 grumbel Exp $
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
#include "Loading.hh"
#include "Display.hh"
#include "OptionMenu.hh"

// Define the global option menu
OptionMenu   option_menu;

// ----- OptionEntry -----

OptionEntry::OptionEntry(std::string s, bool* v, int x, int y)
{
  font = PingusResource::load_font("Fonts/smallfont_h", "fonts");
  str = s;
  value_bool = v;
  value_int = 0;
  value_str = 0;
  x_pos = x;
  y_pos = y;
}

OptionEntry::OptionEntry(std::string s, std::string* v, int x, int y)
{
  font = PingusResource::load_font("Fonts/smallfont_h", "fonts");
  str = s;
  value_str = v;
  value_int = 0;
  value_bool = 0;
  x_pos = x;
  y_pos = y;
}

OptionEntry::OptionEntry(std::string s, int* v, int x, int y)
{
  font = PingusResource::load_font("Fonts/smallfont_h", "fonts");
  str = s;
  value_str = 0;
  value_int = v;
  value_bool = 0;
  x_pos = x;
  y_pos = y;
}

void
OptionEntry::draw()
{
  if (!mouse_over()) {
    CL_Display::fill_rect(x_pos - 7, y_pos - 1,
			  x_pos + CL_Display::get_width() - 35, y_pos + 11,
			  0.5, 0.5, 0.5, 0.5);
  } else {
    CL_Display::fill_rect(x_pos - 7, y_pos - 1,
			  x_pos + CL_Display::get_width() - 35, y_pos + 11,
			  1.0, 1.0, 1.0, 0.5);
  }
  font->print_left(x_pos, y_pos, str.c_str());

  if (value_bool) {
    if (*value_bool) {
      font->print_right(x_pos + CL_Display::get_width() - 35, y_pos, "on");
    } else {
      font->print_right(x_pos + CL_Display::get_width() - 35, y_pos, "off");
    }
  } else if (value_str) {
    font->print_right(x_pos + CL_Display::get_width() - 35, y_pos, value_str->c_str());    
  } else if (value_int) {
    char str[256];
    sprintf(str, "%d", *value_int);
    font->print_right(x_pos + CL_Display::get_width() - 35, y_pos, str);    
  }
}

void
OptionEntry::toggle()
{
  if (value_bool) {
    *(value_bool) = !*(value_bool);
  } else if (value_str) {
    std::cout << "Not implemented" << std::endl;
  } else if (value_int) {
    ++(*value_int);
  }
}

void
OptionEntry::rtoggle()
{
  if (value_bool) {
    *(value_bool) = !*(value_bool);
  } else if (value_str) {
    std::cout << "Not implemented" << std::endl;
  } else if (value_int) {
    --(*value_int);    
  }
}

bool
OptionEntry::mouse_over()
{
  if (CL_Mouse::get_x() > x_pos && CL_Mouse::get_x() < x_pos + CL_Display::get_width() - 30
      && CL_Mouse::get_y() > y_pos && CL_Mouse::get_y() < y_pos + 15) {
    return true;
  } else {
    return false;
  }
}

bool
OptionMenu::Event::on_button_press(CL_InputDevice *device, const CL_Key &key)
{
  return true;
}

bool
OptionMenu::Event::on_button_release(CL_InputDevice *device, const CL_Key &key)
{
  if (device == CL_Input::keyboards[0])
    {
      switch(key.id)
	{
	case CL_KEY_ESCAPE:
	  option_menu->quit = true;
	  break;
	default:
	  if (verbose) std::cout << "OptionMenu::Event: Unknown key released: id=" << key.id << std::endl;
	  break;
	} 
    }
  else if (device == CL_Input::pointers[0])
    {
      switch(key.id)
	{
	case 0:
	  if (verbose) std::cout << "Button 0 pressed" << std::endl;
	  break;
	case 1:
	  option_menu->quit = true;
	  if (verbose) std::cout << "Button 1 pressed" << std::endl;
	  break;
	case 2:
	  if (verbose) std::cout << "Button 2 pressed" << std::endl;
	  break;
	default:
	  if (verbose) std::cout << "OptionMenu::Event: Unknown mouse key released: id=" << key.id << std::endl;
	  break;  
	}
    }

  return true;
}

// ----- OptionMenu -----

OptionMenu::OptionMenu()
{
  quit = false;
  is_init = false;

  event = new Event;
  event->option_menu = this;
}

OptionMenu::~OptionMenu()
{
  delete event;
}

void
OptionMenu::init() 
{
  if (!preload_data)
    loading_screen.draw();

  font       = PingusResource::load_font("Fonts/smallfont_h",  "fonts");
  title_font = PingusResource::load_font("Fonts/pingus", "fonts");
  background =  PingusResource::load_surface("Textures/rocktile", "textures");
  back       = PingusResource::load_surface("Buttons/back", "menu");

  entry_x = 20;
  entry_y = 60;
  is_init = true;

  // Bool options
  add_entry("Gimmicks",  &gimmicks_enabled);
  add_entry("Unlimited Actions",  &unlimited_actions);
  add_entry("Print fps", &print_fps);
  //  add_entry("Debug actions", &debug_actions);  
  add_entry("Cursor enabled", &cursor_enabled);  
  add_entry("Fast Mode", &fast_mode);
  add_entry("Pingus Datadir", &pingus_datadir);
  add_entry("Game Speed", &game_speed);
  add_entry("Verbose", &verbose);
  add_entry("Music", &music_enabled);
  add_entry("Sound", &sound_enabled);
  add_entry("Level Previews", &previews_enabled);
  add_entry("Draw ColMap", &draw_collision_map);
  add_entry("Horizontal Button Panel", &horizontal_button_panel);
  add_entry("Debug GameTime", &debug_game_time);
  add_entry("Debug Tiles", &debug_tiles);
  add_entry("Auto Scrolling", &auto_scrolling);
}

void
OptionMenu::add_entry(std::string e, bool* v)
{
  entry.push_back(OptionEntry(e, v, entry_x, entry_y));
  entry_y += 20;
}

void 
OptionMenu::add_entry(std::string e, int* v)
{
  entry.push_back(OptionEntry(e, v, entry_x, entry_y));
  entry_y += 20;
}

void 
OptionMenu::add_entry(std::string e, std::string* v)
{
  entry.push_back(OptionEntry(e, v, entry_x, entry_y));
  entry_y += 20;
}

void
OptionMenu::draw_background()
{
  for(int y=0; y < CL_Display::get_height(); y += background->get_height()) {
    for(int x=0; x < CL_Display::get_width(); x += background->get_width()) {
      background->put_screen(x, y);
    }
  }
}

void
OptionMenu::draw()
{  
  draw_background();
  
  title_font->print_center(CL_Display::get_width() / 2, 10, "Pingus Option Menu");

  for(EntryIter item = entry.begin(); item != entry.end(); ++item) {
    item->draw();
  }

  back->put_screen(0, 0);
  if (CL_Mouse::get_x() < (int)back->get_width()
      && CL_Mouse::get_y() < (int)back->get_height())
    CL_Display::fill_rect(0, 0, back->get_width(), back->get_height(),
			  1.0, 1.0, 1.0, 0.3);
  Display::flip_display();
}

void
OptionMenu::check_click()
{
  for(EntryIter item = entry.begin(); item != entry.end(); ++item) {
    if (item->mouse_over()) {
      item->toggle();
      break;
    }
  }
}

void
OptionMenu::display()
{
  if (!is_init)
    init();

  //int temp_index = -2;
  //int index = -2;
  EntryIter item = EntryIter();
  EntryIter temp_item = EntryIter();
  int mouse_x = -1, mouse_y = -1;
  
  while(CL_Mouse::left_pressed())
    CL_System::keep_alive();

  quit = false;

  CL_Input::chain_button_press.push_back(event);
  CL_Input::chain_button_release.push_back(event);

  Display::set_cursor(CL_MouseCursorProvider::load("Cursors/cursor",
						   PingusResource::get("game")));
  Display::show_cursor();

  draw();

  while(!quit)
    {
      item = current_item();

      /*      if (temp_item != item || (cursor_enabled 
				&& mouse_x != CL_Mouse::get_x()
				&& mouse_y != CL_Mouse::get_y()))*/
	{
	  mouse_x = CL_Mouse::get_x();
	  mouse_y = CL_Mouse::get_y();
	  draw();
	  temp_item = item;
	}

      if (CL_Mouse::left_pressed()) 
	{
	  if (CL_Mouse::get_x() < (int)back->get_width() &&
	      CL_Mouse::get_y() < (int)back->get_height())
	    {
	      quit = true;	      
	    }

	  if (item != EntryIter()) 
	    item->toggle();
	  draw();
	  while(CL_Mouse::left_pressed())
	    CL_System::keep_alive();
	}

      if (CL_Mouse::right_pressed()) 
	{
	  if (item != EntryIter()) 
	    item->rtoggle();
	  draw();
	  while(CL_Mouse::right_pressed())
	    CL_System::keep_alive();
	}
      CL_System::keep_alive();
    }

  Display::hide_cursor();

  CL_Input::chain_button_release.remove(event);
  CL_Input::chain_button_press.remove(event);
}

std::vector<OptionEntry>::iterator
OptionMenu::current_item()
{
  for(EntryIter item = entry.begin(); item != entry.end(); ++item) {
    if (item->mouse_over()) {
      return item;
    }
  }
  return std::vector<OptionEntry>::iterator();
}

/* EOF */

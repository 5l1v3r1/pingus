 //  $Id: theme.cxx,v 1.23 2003/10/22 11:11:22 grumbel Exp $
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

#include <fstream>
#include <iostream>
#include <ClanLib/Core/System/error.h>
#include <ClanLib/Display/display.h>
#include <ClanLib/Display/font.h>
#include <ClanLib/Display/keyboard.h>
#include "path_manager.hxx"
#include "system.hxx"
#include "resource.hxx"
#include "pingus_error.hxx"
#include "plf_res_mgr.hxx"
#include "game_session.hxx"
#include "globals.hxx"
#include "theme.hxx"
#include "xml_pingus_level.hxx"
#include "fonts.hxx"
#include "gui/screen_manager.hxx"

namespace Pingus {

Theme::Theme (const std::string& filename_)
  : font(Fonts::pingus_small),
    title(Fonts::pingus_large),
    filename (filename_),
    is_loaded(false)
{
}

Theme::~Theme ()
{
}

void
Theme::load (const std::string& filename)
{
  if (verbose) std::cout << "Theme: loading: " << filename << std::endl;
  plt.parse(filename);
  
  title_name = System::translate(plt.get_name());

  level_filenames = plt.get_levels();
  load_levels();

  if (System::translate(plt.get_description()) != "-")
    {
      description.set_font(font);
      description.set_text(System::translate(plt.get_description()), 350);
      has_description = true;
    }
  else
    {
      has_description = false;
    }

  try
    {
      //if (plt.get_background().desc.res_name != "-")
      background = Resource::load_surface("textures/default");
    }
  catch (CL_Error& err)
    {
      if (verbose)
	{
	  std::cout << "Theme:" << filename  << ":" << err.message << std::endl;
	  std::cout << "Theme: Ignoring missing resource, disable background." << std::endl;
	}
    }
  load_status(filename);
}

int
Theme::mark_level_at_point(int x, int y)
{
#ifdef CLANLIB_0_6
  preload ();

  int j = 0;
  int y_pos = level_start_y_pos;

  for(std::vector<std::string>::iterator i = levelnames.begin();
      i < levelnames.end();
      ++i, ++j)
    {
      int width = font.get_text_width(i->c_str());

      if ((CL_Display::get_width()/2 - width/2) < x
	  && (CL_Display::get_width()/2 + width/2) > x
	  && y_pos < y
	  && (y_pos + font.get_height()) > y)
	{
	  if (j <= accessible_levels)
	    {
	      current_level = j;
	      // std::cout << "Current_level: " << current_level << std::endl;
	      return current_level;
	    }
	  return -1;
	}
      y_pos += font.get_height() + 4;
    }
#endif
  return -1;
}

void
Theme::draw_title()
{
#ifdef CLANLIB_0_6
  preload ();

  int x_center =  CL_Display::get_width() / 2;
  int x_pos = x_center;
  int y_pos = 10;

  if (!background)
    {
      CL_Display::clear();
    }
  else
    {
      // Fill the screen with the background surface
      for(int y=0; y < CL_Display::get_height(); y += background.get_height())
	{
	  for(int x=0; x < CL_Display::get_width(); x += background.get_width())
	    background.draw(x, y);
	}
    }

  if (title_name != "-")
    {
      title->print_center(x_center, y_pos, title_name.c_str());
      y_pos += 50;
    }

  if (surface)
    {
      x_pos -= surface.get_width() / 2;
      surface.draw(x_pos, y_pos);

      y_pos += surface.get_height() + 20;
    }

  y_pos += 15;
  if (has_description)
    {
      CL_Display::fill_rect(x_center - (description.get_width()/2) - 15,
			    y_pos - 15,
			    x_center + (description.get_width()/2) + 15,
			    y_pos + description.get_height() + 15,
			    0.0, 0.0, 0.0, 0.5);

      description.print_center(x_center, y_pos);
    }

  y_pos += description.get_height() + 15 + 20;
  int j = 0;

  level_start_y_pos = y_pos;

  for(std::vector<std::string>::iterator i = levelnames.begin(); i != levelnames.end(); ++i)
    {
      if (j > accessible_levels)
	{
	  // Level is not yet accessible
	  font.print_center(x_center, y_pos, (*i).c_str());
	  CL_Display::fill_rect(x_center - font.get_text_width(i->c_str())/2 - 1,
				y_pos - 1,
				x_center + font.get_text_width(i->c_str())/2 + 1,
				y_pos + font.get_height() + 1,
				0.0, 0.0, 0.0, 0.5);
	}
      else if (j == current_level)
	{
	  // Level is accessible
	  CL_Display::fill_rect(x_center - font.get_text_width(i->c_str())/2 - 1,
				y_pos - 1,
				x_center + font.get_text_width(i->c_str())/2 + 1,
				y_pos + font.get_height() + 1,
				0.0f, 0.0f, 0.0f, 1.0f);
	  CL_Display::draw_rect(x_center - font.get_text_width(i->c_str())/2 - 1,
				y_pos - 1,
				x_center + font.get_text_width(i->c_str())/2 + 1,
				y_pos + font.get_height() + 1,
				1.0f, 1.0f, 1.0f, 1.0f);
	  font.print_center(x_center, y_pos, (*i).c_str());
	}
      else
	{
	  font.print_center(x_center, y_pos, (*i).c_str());
	}
      ++j;
      y_pos += font.get_height() + 4;
    }
#endif
}

void
Theme::load_status(std::string name)
{
  status_file = System::basename(name);
  std::string rawname  = status_file.substr(0, status_file.rfind("."));

  if (verbose > 1) std::cout << "Filename: " << status_file << std::endl;
  if (verbose > 1) std::cout << "Rawfile: " << status_file.substr(0, status_file.rfind(".")) << std::endl;

  status_file = System::get_statdir() + "savegames/" + rawname + ".pst";

  if (verbose > 1) std::cout << "Filename to open: " << status_file << std::endl;

  if (System::exist(status_file))
    {
      std::ifstream in;
      in.open(status_file.c_str());
      in >> accessible_levels;
      in.close();
    }
  else
    {
      if (verbose) std::cout << "Theme: No Savegame for this theme found" << std::endl;
      accessible_levels = 0;
    }

  if ((unsigned int)(accessible_levels) >= level_filenames.size())
    {
      if (verbose) std::cout << "Warning: Accessible_Level is to high! " << accessible_levels << std::endl;
      accessible_levels = static_cast<int>(level_filenames.size()) - 1;
    }
  current_level = accessible_levels;
}

void
Theme::play()
{
  preload ();

  try
    {
      assert (!"Theme::play unimplemented");

      ScreenManager::instance()->push_screen
	(new PingusGameSession(PLFResMgr::load_plf(plt.get_levels()[current_level]), true),
         true);

      if (current_level == accessible_levels)
	++accessible_levels;

      if ((unsigned int)(accessible_levels) >= level_filenames.size())
	accessible_levels = static_cast<int>(level_filenames.size()) - 1;

      std::ofstream out (status_file.c_str());
      out << accessible_levels;
      out.close();
    }

  catch (PingusError& err)
    {
      std::cout <<  "Pingus_Error: " << err.get_message () << std::endl;
    }

  // Wait for escape release
  while (CL_Keyboard::get_keycode (CL_KEY_ESCAPE))
    CL_System::keep_alive ();
}

void
Theme::next_level()
{
  preload ();

  ++current_level;

  if ((unsigned int)(current_level) >= level_filenames.size())
    current_level = static_cast<int>(level_filenames.size()) - 1;

  if (current_level > accessible_levels)
    current_level  = accessible_levels;

  //std::cout << "Level: " << current_level << std::endl;
}

void
Theme::previous_level()
{
  preload ();

  current_level--;

  if (current_level < 0)
    current_level = 0;

  //  std::cout << "Level: " << current_level << std::endl;
}

void
Theme::load_levels()
{
  std::string filename;

  if (verbose)
    std::cout << "Theme opening levels... " << std::flush;

  for(std::vector<std::string>::iterator i = level_filenames.begin();
      i != level_filenames.end(); ++i)
    {
      filename = path_manager.complete("levels/" + *i);

      try
	      {
                XMLPingusLevel plf(filename, filename);
	        levelnames.push_back(System::translate(plf.get_levelname()));
	      }
	    catch (PingusError& err)
	      {
	        std::cout << "Theme: PingusError: " << err.get_message () << std::endl;
	      }
    }
  if (verbose)
    std::cout << "done." << std::endl;

  std::cout << "Levelnames: " << static_cast<unsigned>(levelnames.size()) << std::endl;
}

void
Theme::preload ()
{
  if (!is_loaded)
    {
      load(filename);
      is_loaded = true;
    }
}

} // namespace Pingus

/* EOF */

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

#ifndef HEADER_CONFIG_MANAGER_HPP
#define HEADER_CONFIG_MANAGER_HPP

#include <string>
#include <boost/signal.hpp>
#include "math/size.hpp"

/** */
class ConfigManager
{
private:
public:
  ConfigManager();
  ~ConfigManager();

  /** Save the configuration to file */
  void save();

  void set_master_volume(int);
  int  get_master_volume();
  boost::signal<void(int)> on_master_volume_change;

  void set_sound_volume(int);
  int  get_sound_volume();
  boost::signal<void(int)> on_sound_volume_change;

  void set_music_volume(int);
  int  get_music_volume();
  boost::signal<void(int)> on_music_volume_change;

  void set_resolution(const Size& size);
  Size get_resolution();
  boost::signal<void(Size)> on_resolution_change;

  void set_fullscreen(bool);
  bool get_fullscreen();
  boost::signal<void(bool)> on_fullscreen_change;

  void set_allow_resize(bool);
  bool get_allow_resize();
  boost::signal<void(bool)> on_allow_reszie_change;

  void set_fast_mode(bool);
  bool get_fast_mode();
  boost::signal<void(bool)> on_fast_mode_change;

  void set_mouse_grab(bool);
  bool get_mouse_grab();
  boost::signal<void(bool)> on_mouse_grab_change;

  void set_print_fps(bool);
  bool get_print_fps();
  boost::signal<void(bool)> on_print_fps_change;

  void set_language(const std::string&);
  std::string get_language();
  boost::signal<void(const std::string&)> on_language_change;

  void set_swcursor(bool);
  bool get_swcursor();
  boost::signal<void(bool)> on_swcursor_change;

  void set_autoscroll(bool);
  bool get_autoscroll();
  boost::signal<void(bool)> on_autoscroll_change;

private:
  ConfigManager (const ConfigManager&);
  ConfigManager& operator= (const ConfigManager&);
};

extern ConfigManager config_manager;

#endif

/* EOF */

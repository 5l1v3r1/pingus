//  $Id: Editor.hh,v 1.7 2000/08/11 01:07:34 grumbel Exp $
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

#ifndef EDITOR_HH
#define EDITOR_HH

#include <string>
#include <list>
#include <ClanLib/core.h>

#include "../PSMParser.hh"
#include "../PLF.hh"
#include "ObjectSelector.hh"
#include "StatusLine.hh"
#include "EditorEvent.hh"
#include "ObjectManager.hh"
#include "Panel.hh"
#include "ScrollMap.hh"

///
class EditorEvent;
class Panel;
class ScrollMap;

class Editor
{
private:
  ///
  EditorEvent* event;
  ///
  friend class EditorEvent;

  ///
  thSlot on_button_press_slot;
  ///
  thSlot on_button_release_slot;
  
  ///
  int event_handler_ref_counter;

  ///
  CL_Font* font;
  ///
  bool quit;

  ///
  int move_x;
  ///
  int move_y;
  ///
  std::string checkpoint;
  ///
  std::string last_level;
  ///
  bool always_animate;

  ///
  Panel*  panel;
  ///
  ScrollMap* scroll_map;
  ///
  ObjectManager object_manager;
  ///
  StatusLine status_line;
  ///
  ObjectSelector object_selector;
  
public:
  ///
  Editor ();
  ///
  ~Editor ();

  ///
  std::string read_string (std::string prefix = "", std::string default_str = "");
  ///
  void edit ();
  ///  EditorObj* get_current_obj();
  void draw ();
  ///
  void draw_noflip();
  ///
  void interactive_move_object();
  ///
  void move_objects();

  ///
  void rect_get_current_objs();

  ///
  bool mouse_moved();

  ///
  void scroll();

  ///
  void register_event_handler();
  ///
  void unregister_event_handler();

  ///
  std::string save_tmp_level ();
};

#endif

/* EOF */


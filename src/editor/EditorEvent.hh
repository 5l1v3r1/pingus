//  $Id: EditorEvent.hh,v 1.3 2000/02/12 20:53:45 grumbel Exp $
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

#ifndef EDITOREVENT_HH
#define EDITOREVENT_HH

#include <ClanLib/core.h>

#include "Editor.hh"
#include "ObjectManager.hh"

class Editor;

class EditorEvent : public CL_Event_ButtonPress, public CL_Event_ButtonRelease
{
private:
  bool is_enabled;
public:
  EditorEvent();
  virtual ~EditorEvent();

  Editor* editor;
  ObjectManager* object_manager;
  
  virtual bool on_button_press(CL_InputDevice *device, const CL_Key &key);
  virtual bool on_button_release(CL_InputDevice *device, const CL_Key &key);

  void enable();
  void disable();

  void set_editor(Editor* e);

  void editor_exit();
  void editor_mark_or_move_object();
  void editor_mark_all_objects();
  void editor_move_object();
  void editor_toggle_background_color();
  void editor_duplicate_current_selection();
  void editor_delete_selected_objects();
  void editor_start_current_level();
  void editor_save_level_as();
  void editor_load_level();
  void editor_new_level();
  void editor_insert_new_object();
};

#endif

/* EOF */

//  $Id: editor_event.hxx,v 1.8 2002/06/30 22:03:13 grumbel Exp $
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

#ifndef HEADER_PINGUS_EDITOR_EDITOR_EVENT_HXX
#define HEADER_PINGUS_EDITOR_EDITOR_EVENT_HXX

#include "../color.hxx"

class CL_Key;
class CL_Font;
class CL_InputDevice;
class Editor;
class ObjectManager;

class EditorEvent //: public CL_Event_ButtonPress, public CL_Event_ButtonRelease
{
private:
  int is_enabled;
  CL_Font* font;

  std::vector<Color> background_colors;

public:
  EditorEvent();
  virtual ~EditorEvent();

  Editor* editor;
  ObjectManager* object_manager;
  
  virtual void on_button_press(CL_InputDevice *device, const CL_Key &key);
  virtual void on_button_release(CL_InputDevice *device, const CL_Key &key);

  void enable();
  void disable();

  void set_editor(Editor* e);

  void editor_convert_selection_to_group();
  void editor_convert_group_to_selection();
  void editor_exit();
  void editor_mark_or_move_object();
  void editor_mark_all_objects();
  void editor_move_object();
  void editor_toggle_background_color();
  void editor_duplicate_current_selection();

  // Groundpiece modifier
  void editor_horizontal_flip_current_selection();
  void editor_vertical_flip_current_selection();
  void editor_rotate_90_current_selection();
  void editor_rotate_270_current_selection();

  void editor_delete_selected_objects();
  void editor_start_current_level();
  void editor_save_level_as();
  void editor_load_level();
  void editor_new_level();
  void editor_insert_new_object();
  void editor_display_help();
  
  // Export the current selection to a meta-obj
  void editor_export_object_group_from_selection ();
  void editor_import_object_group ();

  /** Display the configuration window for the actions */
  void editor_show_actions_window ();
  
  /** Display the propertie dialog for the current object */
  void editor_show_object_properties ();

  /** Decrease the owner number or another value specific to the
      current object */
  void editor_increase_count ();

  /** Increase the owner number or another value specific to the
      current object */
  void editor_decrease_count ();

  void editor_zoom_in ();
  void editor_zoom_out ();
  void zoom_mode ();

private:
  bool accept_input ();
};

#endif

/* EOF */

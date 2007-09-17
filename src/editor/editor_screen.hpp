//  $Id$
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2007 Jason Green <jave27@gmail.com>,
//                     Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_EDITOR_SCREEN_HXX
#define HEADER_PINGUS_EDITOR_SCREEN_HXX

#include "../gui/gui_screen.hpp"
#include "file_load_dialog.hpp"

class DrawingContext;
class FileDialog;
class GUI::GUIManager;
class Pathname;

namespace Editor {

class EditorLevel;
class LevelObj;
class Panel;
class EditorViewport;
class ObjectSelector;
class ObjectProperties;
class ActionProperties;
class LevelProperties;

/** This class is the screen that contains all of the
    editor objects */
class EditorScreen : public GUIScreen
{
private:
  EditorLevel* plf;

  Panel* panel;
  EditorViewport*   viewport;
  ObjectSelector*   object_selector;
  ObjectProperties* object_properties;
  ActionProperties* action_properties;
  LevelProperties*  level_properties;
  FileDialog*   file_dialog;
  
  bool show_help;

public:
  /** Default constructor */
  EditorScreen();

  /** Destructor */
  ~EditorScreen();

  /** Closes the current screen */
  void close_screen();

  /** Code that runs when the Escape button is pressed */
  void on_escape_press();

  /** Draw the items in the screen */
  bool draw (DrawingContext& gc);

  /** Update the GUI objects */
  void update (const GameDelta& delta);

  /** Return the gui_manager */
  GUI::GUIManager* get_gui_manager() const { return gui_manager; }
	
  /** Return the viewport */
  EditorViewport* get_viewport() const { return viewport; }

  /** Return a pointer to the current level */
  EditorLevel* get_level() const { return plf; }

  /** Add an object to both the EditorLevel and the EditorViewport */
  void add_object(LevelObj* obj);
  void add_objects(std::vector<LevelObj*> objs);

  /** Show a file dialog box */
  void show_file_dialog(bool for_loading);

  /** Closes the file dialog box */
  void cancel();

  /** Saves the currently loaded level */
  void save(const std::string &file);

  /** Load a new level */
  void load(const Pathname& file);

  // Functions accessible from the GUI
  void level_new();
  void level_load();
  void level_save();
  void level_save_as();
  void level_play();

  void objects_delete();

  void objects_raise_to_top();
  void objects_raise();
  void objects_lower();
  void objects_lower_to_bottom();

  void objects_flip_vertical();
  void objects_flip_horizontal();

  void objects_rotate_left();
  void objects_rotate_right();

  void toggle_grid_snap();

  void toggle_object_selector();

  void toggle_object_properties();
  void toggle_action_properties();
  void toggle_level_properties();

  void toggle_help();

  void exit();

private:
  EditorScreen (const EditorScreen&);
  EditorScreen& operator= (const EditorScreen&);

};

} // namespace Editor 

#endif

/* EOF */

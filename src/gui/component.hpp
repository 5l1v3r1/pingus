//  $Id$
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

#ifndef HEADER_PINGUS_GUI_COMPONENT_HXX
#define HEADER_PINGUS_GUI_COMPONENT_HXX

#include "../pingus.hpp"

class DrawingContext;

namespace GUI {

/** A component represents an area which recivies events in the GUI,
    some people might call it a widget */
class Component
{
private:
	
protected:
  bool has_focus;

public:
  Component () : has_focus(false) { }
  virtual ~Component() {}

  virtual void set_focus(bool val) { has_focus = val; }
	
  virtual void draw (DrawingContext& gc) =0;
  virtual void update (float delta) { UNUSED_ARG(delta);}

  virtual bool is_at (int x, int y) { UNUSED_ARG(x); UNUSED_ARG(y); return false; }

  // Events
  /** Gets issued once the primary button is pressed */
  virtual void on_primary_button_press (int x, int y) { UNUSED_ARG(x); UNUSED_ARG(y); }

  /** Gets issued once the primary button is released */
  virtual void on_primary_button_release (int x, int y) { UNUSED_ARG(x); UNUSED_ARG(y); }

  virtual void on_primary_button_double_click (int x, int y) { UNUSED_ARG(x); UNUSED_ARG(y); }

  virtual void on_secondary_button_press (int x, int y) { UNUSED_ARG(x); UNUSED_ARG(y); }
  virtual void on_secondary_button_release (int x, int y) { UNUSED_ARG(x); UNUSED_ARG(y); }

  /** Gets emmited when a button is pressed and released over the
      same component */
  virtual void on_primary_button_click (int x, int y) { UNUSED_ARG(x); UNUSED_ARG(y); }

  virtual void on_secondary_button_click (int x, int y) { UNUSED_ARG(x); UNUSED_ARG(y); }

  /** Emmitted when pointer enters the region of the component */
  virtual void on_pointer_enter () {}

  /** Emmitted when pointer leaves the region of the component */
  virtual void on_pointer_leave () {}

  /** Emitted when the pointer moved, x and y are the new pointer
      coordinates */
  virtual void on_pointer_move (int x, int y) { UNUSED_ARG(x); UNUSED_ARG(y); }
	
  /** Emitted whenever a keyboard character is pressed.  Only certain 
      components should implement this */
  virtual void on_key_pressed(const unsigned short c) { UNUSED_ARG(c); }

private:
  Component (const Component&);
  Component& operator= (const Component&);
};

} // namespace GUI

#endif

/* EOF */

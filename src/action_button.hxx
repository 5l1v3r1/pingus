//  $Id: action_button.hxx,v 1.5 2002/08/02 11:25:46 grumbel Exp $
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

#ifndef HEADER_PINGUS_ACTION_BUTTON_HXX
#define HEADER_PINGUS_ACTION_BUTTON_HXX

#include <ClanLib/Display/Display/surface.h>
#include <string>
#include "anim_counter.hxx"
#include "pingu_enums.hxx"
#include "gui/component.hxx"

using Pingus::Actions::ActionName;

class Server;
class ActionHolder;
class CL_Font;
class CL_Vector;

// ----------------- snip --------------------
class Button
{
protected:
  int x_pos;
  int y_pos;

  CL_Surface surface;
  bool pressed;
public:
  Button();
  Button (int x, int y);
  virtual ~Button();

  virtual void   draw() = 0;
  virtual bool   mouse_over (int x, int y) = 0;
};

// ----------------- snip --------------------
///
class ArmageddonButton : public GUI::Component
{
private:
  int x_pos;
  int y_pos;
  bool pressed;
  CL_Surface surface;
  CL_Surface background;
  CL_Surface backgroundhl;

  AnimCounter counter;
  Server* server;
  friend class ButtonPanel;
public:
  ArmageddonButton(int x, int y);
  virtual ~ArmageddonButton();

  void draw();
  bool is_at(int x, int y);
};

// ----------------- snip --------------------

///
class ForwardButton : public Button
{
private:
  CL_Surface background;
  CL_Surface backgroundhl;
  Server* server;
  friend class ButtonPanel;
public:
  ForwardButton(int x, int y);
  virtual ~ForwardButton();

  void draw();
  bool mouse_over (int x, int y);
};

// ----------------- snip --------------------

///
class PauseButton : public Button
{
private:
  CL_Surface background;
  CL_Surface backgroundhl;
  Server* server;
  friend class ButtonPanel;
public:
  PauseButton(int x, int y);
  virtual ~PauseButton();

  void draw();
  bool mouse_over (int x, int y);
};

// ----------------- snip --------------------

/** The button class manage a simple button for the button_panel. It
    keeps his position, his surfaces and his font. */
class ActionButton : public Button
{
protected:
  CL_Font*    font;
  CL_Font*    font_h;
  // Added for printing action names next to the button.
  CL_Font*    font_b;

  ActionName name;
  int available;
  bool is_multi_direct;

  ActionHolder* action_holder;
  AnimCounter action_c;
public:  
  bool pressed;

  ActionButton();
  virtual ~ActionButton();

  void init(int x, int y, ActionName name_, int owner_id);

  /// Draws the button and increase the animation counter.
  virtual void   draw() = 0;
 
  /// Not used.
  void   update(float delta);

  /// Returns the name of the action the button represents.
  ActionName get_action_name();

  /// Returns true if the button is pressed.
  bool   is_pressed();

  virtual bool   mouse_over(int x, int y) = 0;

  void set_action_holder(ActionHolder* h);
};

// ----------------- snip --------------------
///
class VerticalActionButton : public ActionButton 
{
private:
  CL_Surface background;
  CL_Surface backgroundhl;

public:
  VerticalActionButton(int x, int y, ActionName name, int owner_id);
  virtual ~VerticalActionButton();

  void draw();
  bool mouse_over (int x, int y);
};

// ----------------- snip --------------------

#endif /* ACTIONBUTTON */

/* EOF */





//  $Id: smallmap.hxx,v 1.16 2003/02/19 10:37:31 grumbel Exp $
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

#ifndef HEADER_PINGUS_SMALLMAP_HXX
#define HEADER_PINGUS_SMALLMAP_HXX

#include <ClanLib/Display/Display/surface.h>
#include "gui/component.hxx"

class CL_Key;
class CL_Canvas;
class Client;
class Sprite;
class Vector;

/** This is the map that appears in the corner of the screen */
class SmallMap : public GUI::Component
{
private:
  Client* client;

  /** Graphic surface of the exit */
  CL_Surface exit_sur;

  /** Graphic surface of the entrance */
  CL_Surface entrance_sur;

  /** Graphic surface for the generated rectanglar background of the small map */
  CL_Surface sur;
  
  /** The canvas that represents the small-colmap */
  CL_Canvas* canvas;

  /** Horizontal position of the small map */
  int x_pos;

  /** Vertical position of the small map */
  int y_pos;

  /** Width of the small map */
  int width;

  /** Height of the small map */
  int height;

  /** Max width of the small map */
  int max_width;

  /** Max height of the small map */
  int max_height;

  /** Indicates whether the playfield should can be scrolled around depending 
      on the position of the cursor in the small map */
  bool scroll_mode;

  /** Width of the rectangle displayed inside the small map */
  int rwidth;

  /** Height of the rectangle displayed inside the small map */
  int rheight;

  bool has_focus;

  /** number of seconds till the smallmap will update itself */
  float update_count;

  unsigned int colmap_serial;

  /** Pointer to the current GC, only valid inside draw() */
  GraphicContext* gc_ptr;

public:
  SmallMap(Client* c);
  virtual ~SmallMap();

  /*{ @name Stuff called from the GUIManager */
  void on_primary_button_press(int x, int y);
  void on_primary_button_release(int x, int y);
  void on_pointer_move(int x, int y);

  // Events
  void on_pointer_enter ();
  void on_pointer_leave ();

  void set_client(Client* c);

  bool is_at (int x, int y);
  bool mouse_over();

  void draw(GraphicContext& gc);
  void update(float delta);
  /*}*/

  /** draws a symbolic sprite onto the smallmap 
      @param sprite the Sprite to draw, it will keep its original size
      @param pos the position to draw it in World COs, it will get
      recalculated to screen CO */
  void draw_sprite(Sprite sprite, Vector pos);
  
private:
  void init();
  void draw_pingus();
  
  SmallMap (const SmallMap&);
  SmallMap& operator= (const SmallMap&);
};

#endif

/* EOF */

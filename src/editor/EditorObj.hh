//  $Id: EditorObj.hh,v 1.3 2000/02/11 16:58:28 grumbel Exp $
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

#ifndef EDITOROBJ_HH
#define EDITOROBJ_HH

#include <fstream>
#include <ClanLib/core.h>

#include "../ResDescriptor.hh"
#include "../exit_data.hh"
#include "../entrance_data.hh"

// FIXME: The definitions for trap_data and hotspot_data should go to
// a seperate file.
#include "../PSMParser.hh"
#include "../Trap.hh"
#include "../PLF.hh"

class EditorObj
{
protected:
  
public:
  // FIXME: Should be friend
  int x_pos, y_pos, z_pos;
  int x_of, y_of;

  struct {
    float r;
    float g;
    float b;
    float a;
  } mark_color;

  CL_Surface* surf;
  ResDescriptor desc;
  
  EditorObj();
  virtual ~EditorObj();

  static EditorObj* create(surface_data);
  static EditorObj* create(entrance_data);
  static EditorObj* create(exit_data);
  static EditorObj* create(trap_data);
  static EditorObj* create(hotspot_data);
  static EditorObj* create(liquid_data);

  virtual void   draw_offset(int, int);
  virtual void   draw_mark_offset(int, int);
  virtual bool   mouse_over(int, int);
  virtual bool   is_in_rect(int x1, int y1, int x2, int y2);
  virtual void   save(ofstream* plf, ofstream* psm) = 0;
  virtual std::string obj_type();
  virtual EditorObj* duplicate() = 0;
};

#endif

/* EOF */


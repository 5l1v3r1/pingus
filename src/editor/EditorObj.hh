//  $Id: EditorObj.hh,v 1.35 2001/08/11 18:53:39 grumbel Exp $
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

#ifndef EDITOROBJ_HH
#define EDITOROBJ_HH

#include <fstream>
#include <string>

#include "../boost/smart_ptr.hpp"
#include "../boost/dummy_ptr.hpp"

class CL_Rect;
class CL_Vector;
class EditorView;
class Editor;

/** Interface for all objects which can be shown in the editor */
class EditorObj
{
private:
  static Editor* editor;

public:
  /** Set the parent editor of all objects */
  static void set_editor(Editor* e) { editor = e; }

  static Editor* get_editor () { return editor; }

  EditorObj ();
  virtual ~EditorObj ();

  /** Draw the object to the given view */
  virtual void draw (boost::dummy_ptr<EditorView> view) =0;

  /** Draw a rectangle or shape around the object to the given view */
  virtual void draw_mark (boost::dummy_ptr<EditorView> view) =0;

  /** Return true when the object is under the given coordinates */
  virtual bool is_over(const CL_Vector&) =0;

  /** Return true if the object is inside the given rectangle */
  virtual bool is_in_rect(const CL_Rect& rect) =0;

  /** Return the z-position of the object, the objects are sorted
      after this value */
  virtual float get_z_pos() =0;

  /** Move the object to the given offset */
  virtual void set_position_offset(const CL_Vector& offset) =0;

  /** Generic operations that can make an object larger, what exactly
      happens is object dependend. Default is to do nothing */
  virtual void make_larger () {}

  /** Generic operations that can make an object smaller, what exactly
      happens is object dependend. Default is to do nothing */
  virtual void make_smaller () {}

  /** Write the given object down into a XML file */
  virtual void write_xml(std::ofstream* xml) =0;

  /** Return a string that is shown in the status line */
  virtual std::string status_line();

  /** Duplicate the given editor object and return a the copied
      object */
  virtual boost::shared_ptr<EditorObj> duplicate() =0;
};

#endif

/* EOF */

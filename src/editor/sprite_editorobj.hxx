//  $Id: sprite_editorobj.hxx,v 1.4 2002/09/06 17:33:29 torangan Exp $
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

#ifndef HEADER_PINGUS_EDITOR_SPRITE_EDITOROBJ_HXX
#define HEADER_PINGUS_EDITOR_SPRITE_EDITOROBJ_HXX

#include "../sprite.hxx"
#include "rect_editorobj.hxx"

class CL_Vector;

class SpriteEditorObj : public RectEditorObj
{
protected:
  Sprite sprite;
  CL_Vector& pos_ref;

public:
  SpriteEditorObj (CL_Vector& arg_pos);

  SpriteEditorObj (const std::string& sur_name,
		   const std::string& datafile,
		   CL_Vector& arg_pos);

  SpriteEditorObj (const ResDescriptor&,
		   CL_Vector& arg_pos);

  /// Return the object width
  virtual int get_width() { return sprite.get_width (); }
  /// Return the object height
  virtual int get_height() { return sprite.get_height (); }

  virtual float get_z_pos();

  virtual CL_Vector get_upper_left_corner();

  virtual void draw (EditorView *);

  virtual void set_position_offset (const CL_Vector& offset);

  /** This will be overritten to provide pixel exact click
      detection */
  virtual bool   is_over (const CL_Vector&);
  
protected:
  SpriteEditorObj (const SpriteEditorObj& old);
  void operator= (const SpriteEditorObj& old);
};

#endif

/* EOF */

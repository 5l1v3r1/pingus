//  $Id: editorobj_group.hxx,v 1.5 2002/06/24 22:52:58 grumbel Exp $
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

#ifndef HEADER_PINGUS_EDITOR_EDITOROBJ_GROUP_HXX
#define HEADER_PINGUS_EDITOR_EDITOROBJ_GROUP_HXX

#include <ClanLib/Core/Math/cl_vector.h>
#include "../boost/smart_ptr.hpp"
#include "editorobj.hxx"
#include <list>

class EditorObjGroup : public EditorObj
{
private:
  std::list<boost::shared_ptr<EditorObj> > objs;
  
  CL_Vector upper_left_corner;
  //int width, height;
  //bool init;
public:
  EditorObjGroup();
  EditorObjGroup(const std::list<boost::shared_ptr<EditorObj> >& arg_objs);
  virtual ~EditorObjGroup();

  float get_z_pos();

  void set_position_offset(const CL_Vector& offset);
  void draw(EditorView *);
  void draw_mark (EditorView * view);
  
  /** Add an object to the group */
  void add (boost::shared_ptr<EditorObj>);
  ///
  std::list<boost::shared_ptr<EditorObj> >* get_objs();
  
  bool is_over(const CL_Vector &);
  bool is_in_rect(const CL_Rect &);
    
  void   write_xml(std::ofstream* xml);
  boost::shared_ptr<EditorObj> duplicate();

  unsigned int size () { return objs.size (); }
};

#endif

/* EOF */




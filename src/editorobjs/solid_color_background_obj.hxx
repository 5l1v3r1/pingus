//  $Id: solid_color_background_obj.hxx,v 1.6 2002/11/29 22:54:23 grumbel Exp $
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

#ifndef HEADER_PINGUS_EDITOROBJS_SOLID_COLOR_BACKGROUND_OBJ_HXX
#define HEADER_PINGUS_EDITOROBJS_SOLID_COLOR_BACKGROUND_OBJ_HXX

#include "../editor/rect_editorobj.hxx"
#include "../editor/editor.hxx"
#include "../editor/generic_property_frame.hxx"
#include "../editor/property_window.hxx"
#include "surface_background_obj.hxx"

using namespace EditorNS;

namespace WorldObjsData {
class SolidColorBackgroundData;
}

namespace EditorObjs {

class SolidColorBackgroundObj : public RectEditorObj
{
private:
  WorldObjsData::SolidColorBackgroundData* const data;
  
public:
  SolidColorBackgroundObj (const WorldObjsData::SolidColorBackgroundData& data_);
 ~SolidColorBackgroundObj ();
 
  void write_xml (std::ostream& xml);

  /// Return the object width
  int get_width () { return 256; }
  
  /// Return the object height
  int get_height () { return 256; }

  EditorObj* duplicate ();

  float get_z_pos ();

  Vector get_upper_left_corner ();

  void draw (EditorNS::EditorView* view);
  
  void set_position_offset (const Vector& offset);  

  std::string status_line ();
  EditorNS::PropertyFrame* get_gui_dialog(EditorNS::Editor*);
private:
  SolidColorBackgroundObj (const SolidColorBackgroundObj&);
  SolidColorBackgroundObj& operator= (const SolidColorBackgroundObj&);
};

} // namespace EditorObjs

#endif

/* EOF */

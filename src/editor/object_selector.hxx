// $Id: object_selector.hxx,v 1.13 2002/09/28 11:52:23 torangan Exp $
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmx.de>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef HEADER_PINGUS_EDITOR_OBJECT_SELECTOR_HXX
#define HEADER_PINGUS_EDITOR_OBJECT_SELECTOR_HXX

#include <config.h>
#include <map>
#include <list>
#include "../vector.hxx"
#include "../groundtype.hxx"
#include "surface_selector.hxx"
#include "editorobj.hxx"

class EditorObj;

namespace EditorNS {

/** The ObjectManager provides a graphical interface to select objects
    in the Editor from a list of objects and insert them into the
    level. */
class ObjectSelector
{
private:
  CL_Font* font;
  
  int x_offset;
  int y_offset;

  Vector pos;

  std::string last_object;
  std::map<std::string, bool> data_loaded;
  
public:
  ObjectSelector();
  ~ObjectSelector();
  
  EditorObjLst select_obj_type();
  std::string select_surface(std::vector<surface_obj>& sur_list);
  std::string select_surface(const std::string & resource_file);
  int    read_key();
  std::string read_string(const std::string &, const std::string &);
  
  EditorObjLst get_obj(int, int);
  EditorObjLst get_trap();
  EditorObjLst get_groundpiece(const Groundtype::GPType& gptype);
  EditorObjLst get_hotspot(const std::string&);
  EditorObjLst get_entrance();
  EditorObjLst get_exit();
  EditorObjLst get_liquid();
  EditorObjLst get_weather();
  EditorObjLst get_worldobj();
  EditorObjLst get_from_file();
  EditorObjLst get_background();
  EditorObjLst get_prefab();
  
private:
  ObjectSelector (const ObjectSelector&);
  ObjectSelector& operator= (const ObjectSelector&);
};

} // namespace EditorNS

#endif

/* EOF */



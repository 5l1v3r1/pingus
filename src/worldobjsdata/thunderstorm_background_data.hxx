//  $Id: thunderstorm_background_data.hxx,v 1.5 2003/03/04 12:53:47 grumbel Exp $
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

#ifndef HEADER_PINGUS_WORLDOBJSDATA_THUNDERSTORM_BACKGROUND_DATA_HXX
#define HEADER_PINGUS_WORLDOBJSDATA_THUNDERSTORM_BACKGROUND_DATA_HXX

#include "../vector.hxx"
#include "../worldobj_data.hxx"
#include "../libxmlfwd.hxx"

namespace WorldObjsData {

class ThunderstormBackgroundData : public WorldObjData
{
public:
  Vector pos;

public:
  ThunderstormBackgroundData () {}
  ThunderstormBackgroundData (xmlDocPtr doc, xmlNodePtr cur);

  ThunderstormBackgroundData (const ThunderstormBackgroundData& old);
 
  /** Writte the content of this object formated as xml to the given
      stream */
  virtual void write_xml (std::ostream& xml);

  void insert_WorldObjs (World* world);
  void insert_EditorObjs (EditorNS::ObjectManager*);

private:  
  ThunderstormBackgroundData& operator= (const ThunderstormBackgroundData&);
};

} // namespace WorldObjsData

#endif

/* EOF */

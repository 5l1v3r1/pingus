//  $Id: hotspot_data.hxx,v 1.4 2002/06/25 12:20:31 grumbel Exp $
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

#ifndef HEADER_PINGUS_HOTSPOT_DATA_HXX
#define HEADER_PINGUS_HOTSPOT_DATA_HXX

#include <ClanLib/Core/Math/cl_vector.h>
#include "res_descriptor.hxx"
#include "worldobj_data.hxx"

#include "libxmlfwd.hxx"

class HotspotData : public WorldObjData
{
public:
  CL_Vector pos;
  int   speed;
  float para;
  ResDescriptor desc;

  HotspotData() {
    clean();
  }
  HotspotData (xmlDocPtr doc, xmlNodePtr cur);


  void clean() {
    pos.x = 0;
    pos.y = 0;
    pos.z = 0;
    speed = -1;
    para = 1.0;
  }

  void write_xml(std::ostream&);

  WorldObj* create_WorldObj();
  EditorObjLst create_EditorObj();
};

#endif

/* EOF */





//  $Id: switch_door_data.hxx,v 1.2 2002/09/15 11:02:24 grumbel Exp $
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

#ifndef HEADER_PINGUS_WORLDOBJSDATA_SWITCH_DOOR_DATA_HXX
#define HEADER_PINGUS_WORLDOBJSDATA_SWITCH_DOOR_DATA_HXX

#include <ClanLib/Core/Math/cl_vector.h>
#include <ClanLib/Display/Display/surface.h>
#include "../worldobj_data.hxx"
#include "../libxmlfwd.hxx"

namespace WorldObjsData {

/** A variable height door which can block the way and which can be
    opened by a switch */
class SwitchDoorData : public WorldObjData
{
public:
  /// The upper/middle pos of the door 
  CL_Vector door_pos;
  
  /// The bottom/middle pos of the switch
  CL_Vector switch_pos;

  // The height of the door in graphic tiles
  int door_height;

  SwitchDoorData ();
  SwitchDoorData (xmlDocPtr doc, xmlNodePtr cur);
  SwitchDoorData (const SwitchDoorData& old);

  /** Write the content of this object formatted as xml to the given
      stream */
  void write_xml (std::ostream& xml);
  
  /** Create an WorldObj from the given data object */
  WorldObj* create_WorldObj ();

  /** Create an EditorObj from the given data object */
  EditorObjLst create_EditorObj ();

private:
  SwitchDoorData operator= (const SwitchDoorData&);
};

} // namespace WorldObjsData

#endif

/* EOF */

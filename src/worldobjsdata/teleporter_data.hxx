//  $Id: teleporter_data.hxx,v 1.7 2003/03/05 19:13:59 grumbel Exp $
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

#ifndef HEADER_PINGUS_WORLDOBJSDATA_TELEPORTER_DATA_HXX
#define HEADER_PINGUS_WORLDOBJSDATA_TELEPORTER_DATA_HXX

#include "../vector.hxx"
#include "../sprite.hxx"
#include "../worldobj_data.hxx"
#include "../libxmlfwd.hxx"

namespace WorldObjsData {

class TeleporterData : public WorldObjData
{
public:
  Vector pos;
  Vector target_pos;
  
  TeleporterData ();
  TeleporterData (xmlDocPtr doc, xmlNodePtr cur);
  TeleporterData (const TeleporterData& data);

  /** Write the content of this object formatted as xml to the given
      stream */
  void write_xml (std::ostream& xml);

  /** Create an WorldObj from the given data object */
  void insert_WorldObjs (World*);

  /** Create an EditorObj from the given data object */
  void insert_EditorObjs (EditorNS::EditorObjMgr*);
  
private:
  TeleporterData& operator= (const TeleporterData& data);
};

} // namespace WorldObjsData

#endif

/* EOF */

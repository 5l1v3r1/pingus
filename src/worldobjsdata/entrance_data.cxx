//  $Id: entrance_data.cxx,v 1.5 2003/02/19 17:17:01 grumbel Exp $
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

#include <iostream>
#include "../editorobjs/entrance_obj.hxx"
#include "../worldobjs/entrances/woodthing.hxx"
#include "../worldobjs/entrances/cloud.hxx"
#include "../pingus_error.hxx"
#include "../string_converter.hxx"
#include "../xml_helper.hxx"
#include "../xml_file_reader.hxx"
#include "entrance_data.hxx"

namespace WorldObjsData {

EntranceData::EntranceData () : direction(MISC),
                                release_rate(50),
				owner_id(0),
				type("generic")
{
}

EntranceData::EntranceData (xmlDocPtr doc, xmlNodePtr cur) : direction(MISC),
                                                             release_rate(50),
							     owner_id(0),
							     type("generic")
{
  XMLFileReader reader(doc,cur);
  reader.read_string("type", type);
  reader.read_int("owner-id", owner_id);
  reader.read_vector("position", pos);
  reader.read_int("release-rate", release_rate);
  
  std::string direction_str;
  reader.read_string("direction", direction_str);

  if (direction_str == "left")
    direction = EntranceData::LEFT;
  else if (direction_str == "right")
    direction = EntranceData::RIGHT;
  else if (direction_str == "misc")
    direction = EntranceData::MISC;
  else
    {
      std::cout << "EntranceData: Unknown direction: '" << direction_str << "'" << std::endl;
      direction = EntranceData::MISC;
    }
}

EntranceData::EntranceData (const EntranceData& old)
  : WorldObjData(old),
    direction(old.direction),
    desc(old.desc),
    pos(old.pos),
    release_rate(old.release_rate),
    owner_id(old.owner_id),
    type(old.type)
{
}

void 
EntranceData::write_xml (std::ostream& xml)
{
  std::string dir_str;
  
  switch(direction)
    {
    case EntranceData::LEFT:
      dir_str = "left";
      break;
    case EntranceData::RIGHT:
      dir_str = "right";
      break;
    case EntranceData::MISC:
    default:
      dir_str = "misc";
      break;
    }

  xml << "<entrance>\n";
  XMLhelper::write_vector_xml(xml, pos);
  xml << "  <type>" << type << "</type>\n"
      << "  <direction>" << dir_str << "</direction>\n"
      << "  <release-rate>" << release_rate << "</release-rate>\n"
      << "  <owner-id>" << owner_id << "</owner-id>\n"
      << "</entrance>\n"
      << std::endl;  
}

WorldObj* 
EntranceData::create_WorldObj ()
{
  if (type == "generic") {
    return new WorldObjs::Entrance(*this);
  } else if (type == "woodthing") {
    return new WorldObjs::Entrances::WoodThing(*this);
  } else if (type == "cloud") {
    return new WorldObjs::Entrances::Cloud(*this);
  } else {
    PingusError::raise("Entrance: Entrance type in Level file is unknown: " + type);
    return 0; // never reached
  }
}

EditorObjLst 
EntranceData::create_EditorObj ()
{
  return EditorObjLst(1, new EditorObjs::EntranceObj(*this));
}

} // namespace WorldObjsData

/* EOF */

//  $Id: switch_door_data.cxx,v 1.11 2003/03/05 19:13:59 grumbel Exp $
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
#include "../world.hxx"
#include "../xml_file_reader.hxx"
#include "../xml_helper.hxx"
#include "../editorobjs/switch_door_obj.hxx"
#include "../worldobjs/switch_door.hxx"
#include "../editor/editorobj_mgr.hxx"
#include "switch_door_data.hxx"

namespace WorldObjsData {

SwitchDoorData::SwitchDoorData () 
  : door_height(10)
{
}

SwitchDoorData::SwitchDoorData (xmlDocPtr doc, xmlNodePtr cur)
{
  XMLFileReader reader(doc, cur);
  XMLFileReader subreader;

  reader.read_section("switch", subreader);
  subreader.read_vector("position", switch_pos);

  reader.read_section("door", subreader);
  subreader.read_vector("position", door_pos);
  subreader.read_int("height", door_height);
}

SwitchDoorData::SwitchDoorData (const SwitchDoorData& old) 
                              : WorldObjData(old),
			        door_pos(old.door_pos),
				switch_pos(old.switch_pos),
				door_height(old.door_height)
{
}

void 
SwitchDoorData::write_xml (std::ostream& xml)
{
  xml << "  <worldobj type=\"switchdoor\">\n";
  xml << "    <switch>\n";
  XMLhelper::write_vector_xml(xml, switch_pos);
  xml << "    </switch>\n"
      << "    <door>\n"
      << "    <height>\n" << door_height << "</height>\n";
  XMLhelper::write_vector_xml(xml, door_pos);
  xml << "    </door>\n"
      << "  </worldobj>\n" << std::endl;
}

/** Create an WorldObj from the given data object */
void
SwitchDoorData::insert_WorldObjs (World* world)
{
  world->add_object(new WorldObjs::SwitchDoor(*this));
}

/** Create an EditorObj from the given data object */
void
SwitchDoorData::insert_EditorObjs (EditorNS::EditorObjMgr* obj_mgr)
{
  EditorObjs::SwitchDoorObj* obj = new EditorObjs::SwitchDoorObj(*this);
  obj_mgr->add(obj);
  obj_mgr->add(new EditorObjs::SwitchDoorSwitchObj(obj));
}

} // namespace WorldObjsData

/* EOF */

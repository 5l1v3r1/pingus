//  $Id: switch_door_data.cxx,v 1.13 2003/10/18 23:17:28 grumbel Exp $
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
#include "../worldobjs/switch_door.hxx"
#include "switch_door_data.hxx"

namespace Pingus {
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

/** Create an WorldObj from the given data object */
void
SwitchDoorData::insert_WorldObjs (World* world)
{
  world->add_object(new WorldObjs::SwitchDoor(*this));
}

} // namespace WorldObjsData
} // namespace Pingus

/* EOF */

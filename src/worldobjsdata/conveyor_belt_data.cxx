//  $Id: conveyor_belt_data.cxx,v 1.13 2003/10/18 23:17:28 grumbel Exp $
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
#include "../xml_file_writer.hxx"
#include "../worldobjs/conveyor_belt.hxx"
#include "conveyor_belt_data.hxx"

namespace Pingus {
namespace WorldObjsData {

ConveyorBeltData::ConveyorBeltData ()
  : width(5),
    speed(2),
    counter(0)
{
}

ConveyorBeltData::ConveyorBeltData (xmlDocPtr doc, xmlNodePtr cur)
{
  XMLFileReader reader(doc, cur);
  reader.read_vector("position", pos);
  reader.read_int("width", width);
  reader.read_float("speed", speed);
}

ConveyorBeltData::ConveyorBeltData (const ConveyorBeltData& old)
  : WorldObjData(old),
    pos(old.pos),
    width(old.width),
    speed(old.speed),
    counter(old.counter)
{
}

void
ConveyorBeltData::insert_WorldObjs (World* world)
{
  world->add_object(new WorldObjs::ConveyorBelt(*this));
}

} // namespace WorldObjsData
} // namespace Pingus

/* EOF */

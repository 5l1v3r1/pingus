//  $Id: laser_exit_data.cxx,v 1.13 2003/10/20 13:11:09 grumbel Exp $
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
#include "laser_exit_data.hxx"
#include "../world.hxx"
#include "../xml_helper.hxx"
#include "../xml_file_reader.hxx"
#include "../worldobjs/laser_exit.hxx"
#include "../resource.hxx"

namespace Pingus {
namespace WorldObjsData {

LaserExitData::LaserExitData ()
{
}

LaserExitData::LaserExitData (xmlDocPtr doc, xmlNodePtr cur) 
  : surface(Resource::load_sprite("traps/laser_exit"))
{
  XMLFileReader reader(doc, cur);
  reader.read_vector("position", pos);
}

LaserExitData::LaserExitData (const LaserExitData& old) : WorldObjData(old),
							  surface(old.surface),
							  pos(old.pos)
{
}

void
LaserExitData::insert_WorldObjs (World* world)
{
  world->add_object(new WorldObjs::LaserExit(*this));
}

} // namespace WorldObjsData
} // namespace Pingus

/* EOF */

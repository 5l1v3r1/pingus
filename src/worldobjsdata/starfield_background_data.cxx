//  $Id: starfield_background_data.cxx,v 1.12 2003/10/18 23:17:28 grumbel Exp $
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
#include "../worldobjs/starfield_background.hxx"
#include "starfield_background_data.hxx"

namespace Pingus {
namespace WorldObjsData {

StarfieldBackgroundData::StarfieldBackgroundData (xmlDocPtr doc, xmlNodePtr cur)
{
  small_stars_count  = 100;
  middle_stars_count =  50;
  large_stars_count  =  25;


  XMLFileReader reader(doc, cur);
  reader.read_int("small-stars",  small_stars_count);
  reader.read_int("middle-stars", middle_stars_count);
  reader.read_int("large-stars",  large_stars_count);
}

void
StarfieldBackgroundData::insert_WorldObjs (World* world)
{
  world->add_object(new WorldObjs::StarfieldBackground(*this));
}

} // namespace WorldObjsData
} // namespace Pingus

/* EOF */

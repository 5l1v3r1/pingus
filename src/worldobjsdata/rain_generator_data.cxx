//  $Id: rain_generator_data.cxx,v 1.3 2002/09/16 17:17:17 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#include <fstream>
#include "../editor/weather_obj.hxx"
#include "../worldobjs/rain_generator.hxx"
#include "rain_generator_data.hxx"

namespace WorldObjsData {

void
RainGeneratorData::write_xml(std::ostream& xml)
{
  xml << "<worldobj type=\"rain-generator\"/>" << std::endl;
}

WorldObj*
RainGeneratorData::create_WorldObj ()
{
  return new WorldObjs::RainGenerator();
}

EditorObjLst
RainGeneratorData::create_EditorObj ()
{
  return EditorObjLst(1, new WeatherObj("rain-generator"));
}

} // namespace WorldObjsData

/* EOF */

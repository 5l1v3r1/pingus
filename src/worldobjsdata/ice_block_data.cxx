//  $Id: ice_block_data.cxx,v 1.7 2003/02/18 10:14:52 grumbel Exp $
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
#include "../xml_file_reader.hxx"
#include "../xml_helper.hxx"
#include "../editorobjs/ice_block_obj.hxx"
#include "../worldobjs/ice_block.hxx"
#include "ice_block_data.hxx"

namespace WorldObjsData {

IceBlockData::IceBlockData () 
  : width(1)
{
}

IceBlockData::IceBlockData (const IceBlockData& old) 
  : WorldObjData(old),
    pos(old.pos),
    width(old.width)
{
}

IceBlockData::IceBlockData (xmlDocPtr doc, xmlNodePtr cur)
{
  XMLFileReader reader(doc, cur);
  reader.read_vector("position", pos);
  reader.read_int("width", width);
}

void
IceBlockData::write_xml (std::ostream& xml)
{
  xml << "  <worldobj type=\"iceblock\">";
  XMLhelper::write_vector_xml (xml, pos);
  xml << "    <width>" << width << "</width>\n"
      << "  </worldobj>\n" << std::endl;
}

WorldObj* 
IceBlockData::create_WorldObj ()
{
  return new WorldObjs::IceBlock(*this);
}

EditorObjLst
IceBlockData::create_EditorObj ()
{
  return EditorObjLst(1, new EditorObjs::IceBlockObj(*this));
}

} // namespace WorldObjsData

/* EOF */

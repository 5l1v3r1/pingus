//  $Id: smasher_data.cxx,v 1.5 2002/09/15 09:54:34 torangan Exp $
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

#include <ostream>
#include "smasher_data.hxx"
#include "../xml_helper.hxx"
#include "../editorobjs/smasher_obj.hxx"
#include "../worldobjs/smasher.hxx"
#include "../pingus_resource.hxx"

namespace WorldObjsData {

SmasherData::SmasherData ()
{
}

SmasherData::SmasherData (xmlDocPtr doc, xmlNodePtr cur) : surface(PingusResource::load_surface("Traps/smasher", "traps"))
{
  cur = cur->children;
  while (cur)
    {
      XMLhelper::skip_blank(cur);

      if (XMLhelper::equal_str(cur->name, "position")) 
	{
	  pos = XMLhelper::parse_vector(doc, cur);
	}
	  
      cur = cur->next;
    }
}

SmasherData::SmasherData (const SmasherData& old) : WorldObjData(old),
						    surface(old.surface),
						    pos(old.pos)
{
}

void
SmasherData::write_xml (std::ostream& xml)
{
  xml << "<worldobj type=\"smasher\">\n\t";
  XMLhelper::write_vector_xml(xml, pos);
  xml << "</worldobj>\n\n";
}

WorldObj*
SmasherData::create_WorldObj ()
{
  return new WorldObjs::Smasher(this);
}

EditorObjLst
SmasherData::create_EditorObj ()
{
  return EditorObjLst(1, new EditorObjs::SmasherObj(*this));
}

} // namespace WorldObjsData

/* EOF */

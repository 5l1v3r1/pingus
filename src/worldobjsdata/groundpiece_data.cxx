//  $Id: groundpiece_data.cxx,v 1.5 2002/09/27 18:36:41 torangan Exp $
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

#include <fstream>
#include "../editorobjs/groundpiece_obj.hxx"
#include "../worldobjs/groundpiece.hxx"
#include "../world.hxx"
#include "../xml_helper.hxx"
#include "groundpiece_data.hxx"

namespace WorldObjsData {

GroundpieceData::GroundpieceData () 
{
  // do nothing
}

GroundpieceData::GroundpieceData (xmlDocPtr doc, xmlNodePtr cur)
{
  gptype = Groundtype::GP_GROUND;

  char* gptype_c_str = XMLhelper::get_prop(cur, "type");
  if (gptype_c_str)
    {
      gptype = Groundtype::string_to_type (gptype_c_str);
      xmlFree(gptype_c_str);
    }
  else
    std::cout << "XMLPLF: groundtype empty, which might be ok." << std::endl;

  cur = cur->children;

  while (cur)
    {
      if (xmlIsBlankNode(cur)) 
	{
	  cur = cur->next;
	  continue;
	}
      
      if (XMLhelper::equal_str(cur->name, "position"))
	{
	  pos = XMLhelper::parse_vector(doc, cur);
	}
      else if (XMLhelper::equal_str(cur->name, "surface"))
	{
	  desc = XMLhelper::parse_surface(doc, cur);
	}
      else if (XMLhelper::equal_str(cur->name, "type"))
	{
	  std::string type = XMLhelper::parse_string(doc, cur);
	  gptype = Groundtype::string_to_type (type);
	}
      else
	{
	  printf("Unhandled: %s\n", (char*)cur->name);
	}
      cur = cur->next;	
    }
}

GroundpieceData::GroundpieceData (const GroundpieceData& old) 
                                 : WorldObjData(old),
				   surface(old.surface),
				   desc(old.desc),
				   pos(old.pos),
				   gptype(old.gptype)
{
}

GroundpieceData&
GroundpieceData::operator= (const GroundpieceData& old)
{
  if (this == &old)
    return *this;
    
  WorldObjData::operator=(old);
  
  surface = old.surface;
  desc    = old.desc;
  pos     = old.pos;
  gptype  = old.gptype;
  
  return *this;
}

GroundpieceData::~GroundpieceData ()
{
}
EditorObjLst
GroundpieceData::create_EditorObj ()
{
  return EditorObjLst(1, new EditorObjs::GroundpieceObj(*this));
}

WorldObj*
GroundpieceData::create_WorldObj ()
{
  return new WorldObjs::Groundpiece(*this);
}

void
GroundpieceData::write_xml(std::ostream& xml)
{
  xml << "<worldobj type=\"groundpiece\">\n";
  xml << "  <type>" << Groundtype::type_to_string(gptype) << "</type>\n";
  XMLhelper::write_desc_xml(xml, desc);
  XMLhelper::write_vector_xml(xml, pos);
  xml << "</worldobj>\n" << std::endl;
}

} // namespace WorldObjsData

/* EOF */

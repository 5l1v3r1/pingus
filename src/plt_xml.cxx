//  $Id: plt_xml.cxx,v 1.13 2003/10/19 12:25:47 grumbel Exp $
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
#include "globals.hxx"
#include "pingus_error.hxx"
#include "xml_helper.hxx"
#include "plt_xml.hxx"

namespace Pingus {

PLTXML::PLTXML ()
{
}

PLTXML::~PLTXML ()
{
}


void
PLTXML::parse (std::string filename)
{
  doc = xmlParseFile(filename.c_str());
  if (doc)
    {
      parse_file();
      xmlFreeDoc(doc);
    }
  else
    {
      PingusError::raise("PLTXML: Couldn't load : " + filename);
    }
}

void
PLTXML::parse_description(xmlNodePtr cur)
{
  std::string desc;
  std::string lang;

  if (XMLhelper::node_list_get_string(doc, cur->children, 1, desc)) {
    if (XMLhelper::get_prop(cur, "lang", lang))
      description[lang] = desc;
    else
      description[default_language] = desc;
  }
}

void
PLTXML::parse_world_name (xmlNodePtr cur)
{
  std::string name;
  std::string lang;

  if (XMLhelper::node_list_get_string(doc, cur->children, 1, name))
    {
      if (XMLhelper::get_prop(cur, "lang", lang))
	world_name[lang] = name;
      else
	world_name[default_language] = name;
    }
}

void
PLTXML::parse_level_list (xmlNodePtr cur)
{
  cur = cur->children;

  while (cur)
    {
      if (XMLhelper::equal_str(cur->name, "level"))
	{
	  std::string name;
	  if (XMLhelper::node_list_get_string(doc, cur->children, 1, name))
	    {
	      level_list.push_back(name);
	    }
	}
      else
	{
	  std::cout << "PLTXML: Unhandled: " << cur->name << std::endl;
	}
      cur = cur->next;
    }
}

void
PLTXML::parse_file()
{
  xmlNodePtr cur = doc->ROOT;

  if (cur && XMLhelper::equal_str(cur->name, "pingus-world"))
    {
      cur = cur->children;

      while (cur)
	{
	  if (XMLhelper::equal_str(cur->name, "description"))
	    {
	      parse_description(cur);
	    }
	  else if (XMLhelper::equal_str(cur->name, "background"))
	    {
	      //parse_background(cur);
	    }
	  else if (XMLhelper::equal_str(cur->name, "world-name"))
	    {
	      parse_world_name(cur);
	    }
	  else if (XMLhelper::equal_str(cur->name, "level-list"))
	    {
	      parse_level_list(cur);
	    }
	  else
	    {
	      std::cout << "PLTXML: Unhandled: " << cur->name << std::endl;
	    }
	  cur = cur->next;
	}
    }
}

std::vector<std::string>
PLTXML::get_levels ()
{
  return level_list;
}

std::map<std::string,std::string>
PLTXML::get_name ()
{
  return world_name;
}

std::map<std::string,std::string>
PLTXML::get_description ()
{

  return description;
}

} // namespace Pingus

/* EOF */

//  $Id: xml_plf.cxx,v 1.15 2002/09/15 20:33:45 grumbel Exp $
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

#include "xml_helper.hxx"
#include "xml_plf.hxx"
#include "globals.hxx"
#include "system.hxx"
#include "pingus_error.hxx"
#include "string_converter.hxx"
#include "worldobj_data_factory.hxx"
#include "worldobjsdata/worldobj_group_data.hxx"
#include "exit_data.hxx"
#include "entrance_data.hxx"
#include "hotspot_data.hxx"
#include "liquid_data.hxx"

using namespace std;
using Actions::action_from_string;

XMLPLF::XMLPLF (const std::string& filename)
{
  //  std::cout << "----- Parsing .xml file" << std::endl;
  //std::cout << "--- Checksum: " << std::flush;
  std::string str = System::checksum (filename);
  //std::cout << str << std::endl;

  doc = xmlParseFile(filename.c_str());

  if (doc == NULL)
    PingusError::raise("XMLPLF: Couldn't open \"" + filename + "\"");

  parse_file();
}

XMLPLF::~XMLPLF()
{
  xmlFreeDoc(doc);
  /*
  // Free all the allocated memory
  for(vector<BackgroundData*>::iterator i = backgrounds.begin ();
  i != backgrounds.end ();
  i++)
  delete *i;

  for(vector<WorldObjData*>::iterator i = worldobjs_data.begin ();
  i != worldobjs_data.end ();
  i++)
  delete *i;
  */
}

void
XMLPLF::parse_file()
{
  //std::cout << "parsing file" << std::endl;
  xmlNodePtr cur = doc->ROOT;

  cur = XMLhelper::skip_blank(cur);

  if (cur && XMLhelper::equal_str(cur->name, "pingus-level"))
    {
      //std::cout << "parse_file...." << std::endl;

      cur = XMLhelper::skip_blank(cur);

      if (!cur->children)
	std::cout << "XMLPLF: node: " << cur->name << std::endl;
      
      cur = cur->children;
      cur = XMLhelper::skip_blank(cur);
      
      while (cur)
	{
	  if (xmlIsBlankNode(cur)) 
	    {
	      cur = cur->next;
	      continue;
	    }

	  // FIXME: This can mostly be unified with the
	  // WorldObjDataFactory, exit, backgrounds, etc. are all
	  // WorldObjs
	  if (XMLhelper::equal_str(cur->name, "global"))
	    {
	      parse_global(cur);
	    }
	  else if (XMLhelper::equal_str(cur->name, "action-list"))
	    {
	      parse_actions(cur);
	    }
	  else if (XMLhelper::equal_str(cur->name, "background"))
	    {
	      parse_background(cur);
	    }
	  else if (XMLhelper::equal_str(cur->name, "groundpiece"))
	    {
	      parse_groundpiece(cur);
	    }
	  else if (XMLhelper::equal_str(cur->name, "exit"))
	    {
	      worldobjs_data.push_back (new ExitData (doc, cur));
	    }
	  else if (XMLhelper::equal_str(cur->name, "entrance"))
	    {
	      worldobjs_data.push_back (new EntranceData (doc, cur));
	    }
	  else if (XMLhelper::equal_str(cur->name, "trap"))
	    {
	      parse_traps(cur);
	    }
	  else if (XMLhelper::equal_str(cur->name, "hotspot"))
	    {
	      worldobjs_data.push_back(new HotspotData (doc, cur));
	    }
	  else if (XMLhelper::equal_str(cur->name, "liquid"))
	    {
	      worldobjs_data.push_back(new LiquidData (doc, cur));
	    }
	  else if (XMLhelper::equal_str(cur->name, "worldobj"))
	    {
	      worldobjs_data.push_back(WorldObjDataFactory::instance()->create (doc, cur));
	    }
	  else if (XMLhelper::equal_str(cur->name, "group"))
	    {
	      worldobjs_data.push_back (new WorldObjGroupData (doc, cur));
	    }
	  else if (XMLhelper::equal_str(cur->name, "start-position"))
	    {
	      parse_start_pos(cur);
	    }
	  else if (XMLhelper::equal_str(cur->name, "weather"))
	    {
	      parse_weather(cur);
	    }	  
	  else
	    {
	      printf("XMLPLF: Unhandled: %s\n", reinterpret_cast<const char*>(cur->name));
	    }
	  cur = cur->next;
	}
      //puts("global done");
    } else {
      PingusError::raise("XMLPLF: This is no valid Pingus level");
    }
}

void
XMLPLF::parse_start_pos (xmlNodePtr cur)
{
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
	  CL_Vector pos = XMLhelper::parse_vector(doc, cur);
	  start_x_pos = static_cast<int>(pos.x);
	  start_y_pos = static_cast<int>(pos.y);
	}
      else
	{
	  std::cout << "XMLPLF::parse_start_pos: " << cur->name << std::endl;
	}
      cur = cur->next;
    }
}

void
XMLPLF::parse_weather (xmlNodePtr cur)
{
  WeatherData weather;
  cur = cur->children;

  while (cur)
    {
      if (xmlIsBlankNode(cur)) 
	{
	  cur = cur->next;
	  continue;
	}
      
      if (XMLhelper::equal_str(cur->name, "type"))
	{
	  weather.type = XMLhelper::parse_string(doc, cur);
	}
      else
	{
	  std::cout << "XMLPLF: Unhandled: " << cur->name << std::endl;
	}
      cur = cur->next;
    }
    
  weathers.push_back(weather);
}

void 
XMLPLF::parse_background (xmlNodePtr cur)
{
  // The allocated objects are delete'd in the destructor
  //FIXME: Repair me backgrounds.push_back(BackgroundData::create (doc, cur));
  char* type_cstr = XMLhelper::get_prop(cur, "type");

  if (type_cstr)
    {
      std::string type (type_cstr);

      worldobjs_data.push_back(WorldObjDataFactory::instance ()
			       ->create (type + "-background", doc, cur));
    }
  else
    {
      worldobjs_data.push_back(WorldObjDataFactory::instance ()
			       ->create ("surface-background", doc, cur));
    }

  xmlFree(type_cstr);
}

void 
XMLPLF::parse_actions (xmlNodePtr cur)
{
  cur = cur->children;

  while (cur)
    {
      if (xmlIsBlankNode(cur)) 
	{
	  cur = cur->next;
	  continue;
	}
 
      ActionData button;
      button.name = action_from_string(reinterpret_cast<const char*>(cur->name));

      char* count = XMLhelper::get_prop(cur, "count");
      if (count)
	{
	  from_string(count, button.number_of);
	  xmlFree(count);
	}
      else
	{
	  //std::cout << "XMLPLF::parse_actions (): No 'count' given, fallback to the old format" << std::endl;
	  char* number = reinterpret_cast<char*>(xmlNodeListGetString(doc, cur->children, 1));
	  if (number) {
	    //std::cout << "xmlNoder..Result: " << number << std::endl;
	    button.number_of = StringConverter::to_int(number);
	  } else {
	    std::cout << "XMLPLF:parse_actions: no action number given" << std::endl;
	  }
	  xmlFree(number);
	}

      actions.push_back(button);
      
      cur = cur->next;
    }      
}

void
XMLPLF::parse_global (xmlNodePtr cur)
{
  cur = cur->children;
  while (cur)
    {
      if (xmlIsBlankNode(cur)) 
	{
	  cur = cur->next;
	  continue;
	}

      if (XMLhelper::equal_str(cur->name, "levelname"))
	{
	  char* name = reinterpret_cast<char*>(xmlNodeListGetString(doc, cur->children, 1));
	  char* lang = XMLhelper::get_prop(cur, "lang");

	  if (name) {
	    if (lang)
	      levelname[lang] = name;
	    else
	      levelname[default_language] = name;
	  }

	  if (name)
	    xmlFree(name);
	  if (lang)
	    xmlFree(lang);
	}
      else if (XMLhelper::equal_str(cur->name, "description"))
	{
	  char* desc = reinterpret_cast<char*>(xmlNodeListGetString(doc, cur->children, 1));
	  char* lang = XMLhelper::get_prop(cur, "lang");

	  if (desc) {
	    if (lang)		    
	      description[lang] = desc;
	    else
	      description[default_language] = desc;
	  }

	  if (desc)
	    xmlFree(desc);	  
	  if (lang)
	    xmlFree(lang);
	}
      else if (XMLhelper::equal_str(cur->name, "author"))
	{
	  char* tmp_author = reinterpret_cast<char*>(xmlNodeListGetString(doc, cur->children, 1));
	  if (tmp_author) {
	    author = tmp_author;
	    xmlFree(tmp_author);
	  }
	  //std::cout << "Author: " << author << " -----------------------" << std::endl;
	}
      else if (XMLhelper::equal_str(cur->name, "number-of-pingus"))
	{
	  number_of_pingus = XMLhelper::parse_int(doc, cur);
	}
      else if (XMLhelper::equal_str(cur->name, "difficulty"))
	{
	  difficulty = XMLhelper::parse_int(doc, cur);
	}
      else if (XMLhelper::equal_str(cur->name, "playable"))
	{
	  playable = XMLhelper::parse_int(doc, cur);
	}
      else if (XMLhelper::equal_str(cur->name, "comment"))
	{
	  comment = XMLhelper::parse_string(doc, cur);
	}
      else if (XMLhelper::equal_str(cur->name, "number-to-save"))
	{
	  number_to_save = XMLhelper::parse_int(doc, cur);
	}
      else if (XMLhelper::equal_str(cur->name, "time"))
	{
	  max_time = XMLhelper::parse_int(doc, cur);
	}
      else if (XMLhelper::equal_str(cur->name, "height"))
	{
	  height = XMLhelper::parse_int(doc, cur);
	}
      else if (XMLhelper::equal_str(cur->name, "width"))
	{
	  width = XMLhelper::parse_int(doc, cur);
	}
      else
	{
	  std::cout << "XMLPLF: global: Unhandled: " << cur->name << std::endl;
	}

      cur = cur->next;
    }
}

void 
XMLPLF::parse_groundpiece (xmlNodePtr cur)
{
  groundpieces.push_back(GroundpieceData (doc, cur));
}

void
XMLPLF::parse_traps (xmlNodePtr cur)
{
  xmlNodePtr cur_ = XMLhelper::skip_blank(cur->children);
  
  if (XMLhelper::equal_str(cur_->name, "type"))
    {
      char* name = reinterpret_cast<char*>(xmlNodeListGetString(doc, cur_->children, 1));
      if (name)
	{
	  worldobjs_data.push_back(WorldObjDataFactory::instance()->create (name, doc, XMLhelper::skip_blank(cur)));
	  xmlFree(name);
	  return;
	}
    }

  std::cout << "XMLPLF::parse_traps: Invalid data structure" << std::endl;
}

/* EOF */

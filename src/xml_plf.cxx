//  $Id: xml_plf.cxx,v 1.5 2002/06/28 15:12:22 torangan Exp $
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

#include "xml_plf.hxx"
#include "xml_helper.hxx"
#include "globals.hxx"
#include "system.hxx"
#include "pingus_error.hxx"
#include "string_converter.hxx"
#include "worldobj_data_factory.hxx"
#include "worldobj_group_data.hxx"
#include "exit_data.hxx"
#include "entrance_data.hxx"
#include "trap_data.hxx"
#include "hotspot_data.hxx"
#include "liquid_data.hxx"

using namespace std;
using Pingus::Actions::action_from_string;

XMLPLF::XMLPLF(const std::string& filename)
{
  //  std::cout << "----- Parsing .xml file" << std::endl;
  //std::cout << "--- Checksum: " << std::flush;
  std::string str = System::checksum (filename);
  //std::cout << str << std::endl;

  doc = xmlParseFile(filename.c_str());

  if (doc == NULL)
    throw PingusError("XMLPLF: Couldn't open \"" + filename + "\"");

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

  if (xmlIsBlankNode(cur)) cur = cur->next;

  if (cur != NULL && strcmp((const char*)cur->name, "pingus-level") == 0)
    {
      //std::cout << "parse_file...." << std::endl;

      if (xmlIsBlankNode(cur)) cur = cur->next;

      if (cur->children == NULL)
	std::cout << "XMLPLF: node: " << cur->name << std::endl;
      
      cur = cur->children;
      if (xmlIsBlankNode(cur)) cur = cur->next;
      
      while (cur != NULL)
	{
	  if (xmlIsBlankNode(cur)) 
	    {
	      cur = cur->next;
	      continue;
	    }

	  //puts("global loop");
	  if (strcmp((char*)cur->name, "global") == 0)
	    {
	      parse_global(cur);
	    }
	  else if (strcmp((char*)cur->name, "action-list") == 0)
	    {
	      parse_actions(cur);
	    }
	  else if (strcmp((char*)cur->name, "background") == 0)
	    {
	      parse_background(cur);
	    }
	  else if (strcmp((char*)cur->name, "groundpiece") == 0)
	    {
	      parse_groundpiece(cur);
	    }
	  else if (strcmp((char*)cur->name, "exit") == 0)
	    {
	      worldobjs_data.push_back (new ExitData (doc, cur));
	    }
	  else if (strcmp((char*)cur->name, "entrance") == 0)
	    {
	      worldobjs_data.push_back (new EntranceData (doc, cur));
	    }
	  else if (strcmp((char*)cur->name, "trap") == 0)
	    {
	      worldobjs_data.push_back (new TrapData (doc, cur));
	    }
	  else if (strcmp((char*)cur->name, "hotspot") == 0)
	    {
	      worldobjs_data.push_back(new HotspotData (doc, cur));
	    }
	  else if (strcmp((char*)cur->name, "liquid") == 0)
	    {
	      worldobjs_data.push_back(new LiquidData (doc, cur));
	    }
	  else if (strcmp ((char*)cur->name, "worldobj") == 0)
	    {
	      worldobjs_data.push_back(WorldObjDataFactory::instance ()->create (doc, cur));
	    }
	  else if (strcmp((char*)cur->name, "group") == 0)
	    {
	      parse_group(cur);
	    }
	  else if (strcmp ((char*)cur->name, "start-position") == 0)
	    {
	      parse_start_pos(cur);
	    }
	  else if (strcmp ((char*)cur->name, "weather") == 0)
	    {
	      parse_weather(cur);
	    }	  
	  else
	    {
	      printf("XMLPLF: Unhandled: %s\n", (char*)cur->name);
	    }
	  cur = cur->next;
	}
      //puts("global done");
    } else {
      throw PingusError("XMLPLF: This is no valid Pingus level");
    }
}

void
XMLPLF::parse_start_pos(xmlNodePtr cur)
{
  cur = cur->children;

  while (cur != NULL)
    {
      if (xmlIsBlankNode(cur)) 
	{
	  cur = cur->next;
	  continue;
	}
      
      if (strcmp((char*)cur->name, "position") == 0)
	{
	  CL_Vector pos = XMLhelper::parse_vector(doc, cur);
	  start_x_pos = int(pos.x);
	  start_y_pos = int(pos.y);
	}
      else
	{
	  std::cout << "XMLPLF::parse_start_pos: " << cur->name << std::endl;
	}
      cur = cur->next;
    }
}

void
XMLPLF::parse_weather(xmlNodePtr cur)
{
  WeatherData weather;
  cur = cur->children;

  while (cur != NULL)
    {
      if (xmlIsBlankNode(cur)) 
	{
	  cur = cur->next;
	  continue;
	}
      
      if (strcmp((char*)cur->name, "type") == 0)
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
XMLPLF::parse_group(xmlNodePtr cur)
{
  cur = cur->children;

  WorldObjGroupData* group = new WorldObjGroupData ();

  while (cur != NULL)
    {
      if (xmlIsBlankNode(cur)) 
	{
	  cur = cur->next;
	  continue;
	}
      
      if (strcmp((char*)cur->name, "groundpiece") == 0)
	{
	  parse_groundpiece(cur);
	}
      else if (strcmp((char*)cur->name, "exit") == 0)
	{
	  group->add (new ExitData (doc, cur));
	}
      else if (strcmp((char*)cur->name, "entrance") == 0)
	{
	  group->add (new EntranceData (doc, cur));
	}
      else if (strcmp((char*)cur->name, "trap") == 0)
	{
	  group->add (new TrapData (doc, cur));
	}
      else if (strcmp((char*)cur->name, "hotspot") == 0)
	{
	  group->add(new HotspotData (doc, cur));
	}
      else if (strcmp((char*)cur->name, "liquid") == 0)
	{
	  group->add(new LiquidData (doc, cur));
	}
      else if (strcmp((char*)cur->name, "group") == 0)
	{
	  parse_group(cur);
	}
      else if (strcmp ((char*)cur->name, "worldobj") == 0)
	{
	  group->add(WorldObjDataFactory::instance ()->create (doc, cur));
	}
      else
	{
	  printf("Unhandled: %s\n", (char*)cur->name);
	}
      cur = cur->next;
    }

  worldobjs_data.push_back (group);
}

void 
XMLPLF::parse_background(xmlNodePtr cur)
{
  // The allocated objects are delete'd in the destructor
  //FIXME: Repair me backgrounds.push_back(BackgroundData::create (doc, cur));
  char* type_cstr = (char*)xmlGetProp(cur, (xmlChar*)"type");

  if (type_cstr != 0)
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

  free (type_cstr);
}

void 
XMLPLF::parse_actions(xmlNodePtr cur)
{
  cur = cur->children;

  while (cur != NULL)
    {
      if (xmlIsBlankNode(cur)) 
	{
	  cur = cur->next;
	  continue;
	}
 
      ActionData button;
      button.name = action_from_string((const char*) cur->name);

      char* count = (char*)xmlGetProp(cur, (xmlChar*)"count");
      if (count)
	{
	  from_string(count, button.number_of);
	  free (count);
	}
      else
	{
	  //std::cout << "XMLPLF::parse_actions (): No 'count' given, fallback to the old format" << std::endl;
	  char* number = (char*)xmlNodeListGetString(doc, cur->children, 1);
	  if (number) {
	    //std::cout << "xmlNoder..Result: " << number << std::endl;
	    button.number_of = StringConverter::to_int(number);
	  } else {
	    std::cout << "XMLPLF:parse_actions: no action number given" << std::endl;
	  }
	  free(number);
	}
      actions.push_back(button);
	  
      cur = cur->next;
    }      
}

void
XMLPLF::parse_global(xmlNodePtr cur)
{
  cur = cur->children;
  while (cur != NULL)
    {
      if (xmlIsBlankNode(cur)) 
	{
	  cur = cur->next;
	  continue;
	}

      if (strcmp((char*)cur->name, "levelname") == 0)
	{
	  char* name = (char*)xmlNodeListGetString(doc, cur->children, 1);
	  char* lang = (char*)xmlGetProp(cur, (xmlChar*)"lang");

	  if (name) {
	    if (lang)
	      levelname[lang] = name;
	    else
	      levelname[default_language] = name;
	  }

	  if (name) free(name);
	  if (lang) free(lang);
	}
      else if (strcmp((char*)cur->name, "description") == 0)
	{
	  char* desc = (char*)xmlNodeListGetString(doc, cur->children, 1);
	  char* lang = (char*)xmlGetProp(cur, (xmlChar*)"lang");

	  if (desc) {
	    if (lang)		    
	      description[lang] = desc;
	    else
	      description[default_language] = desc;
	  }

	  if (desc) free(desc);	  
	  if (lang) free(lang);
	}
      else if (strcmp((char*)cur->name, "author") == 0)
	{
	  char* tmp_author = (char*)xmlNodeListGetString(doc, cur->children, 1);
	  if (tmp_author) {
	    author = tmp_author;
	    free(tmp_author);
	  }
	  //std::cout << "Author: " << author << " -----------------------" << std::endl;
	}
      else if (strcmp((char*)cur->name, "number-of-pingus") == 0)
	{
	  number_of_pingus = XMLhelper::parse_int(doc, cur);
	}
      else if (strcmp((char*)cur->name, "difficulty") == 0)
	{
	  difficulty = XMLhelper::parse_int(doc, cur);
	}
      else if (strcmp((char*)cur->name, "playable") == 0)
	{
	  playable = XMLhelper::parse_int(doc, cur);
	}
      else if (strcmp((char*)cur->name, "comment") == 0)
	{
	  comment = XMLhelper::parse_string(doc, cur);
	}
      else if (strcmp((char*)cur->name, "number-to-save") == 0)
	{
	  number_to_save = XMLhelper::parse_int(doc, cur);
	}
      else if (strcmp((char*)cur->name, "time") == 0)
	{
	  max_time = XMLhelper::parse_int(doc, cur);
	}
      else if (strcmp((char*)cur->name, "height") == 0)
	{
	  height = XMLhelper::parse_int(doc, cur);
	}
      else if (strcmp((char*)cur->name, "width") == 0)
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
XMLPLF::parse_groundpiece(xmlNodePtr cur)
{
  groundpieces.push_back(GroundpieceData (doc, cur));
}

/* EOF */

//  $Id: PingusWorldMapGraph.cc,v 1.30 2002/06/04 21:23:42 grumbel Exp $
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

#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "../System.hh"
#include "../my_gettext.hh"
#include "../globals.hh"
#include "../PingusError.hh"
#include "../PathManager.hh"
#include "../XMLPLF.hh"
#include "../Console.hh"
#include "../XMLhelper.hh"
#include "../StringConverter.hh"
#include "../PingusSound.hh"
#include "../PingusGameSession.hh"
#include "PingusWorldMapManager.hh"
#include "PingusWorldMapNode.hh"
#include "PingusWorldMapGraph.hh"

PingusWorldMapGraph::PingusWorldMapGraph ()
{
  music = "pingus-1.it";
  //graph = 0;
}

PingusWorldMapGraph::~PingusWorldMapGraph ()
{
  //llif (graph) delete graph;
}
 
void
PingusWorldMapGraph::parse_file (std::string filename)
{
  doc = xmlParseFile(filename.c_str());

  if (!doc) {
    throw PingusError (_("PingusWorldMapGraph: File not found: ") + filename);
  }    

  xmlNodePtr cur = doc->ROOT;

  if (cur != NULL && strcmp((const char*)cur->name, "pingus-worldmap") == 0)
    {
      cur = cur->children;
      
      while (cur != NULL)
	{
	  if (xmlIsBlankNode(cur)) 
	    {
	      cur = cur->next;
	      continue;
	    }

	  if (strcmp ((char*)cur->name, "node-list") == 0)
	    {
	      parse_node_list (cur);
	    }
	  else if (strcmp ((char*)cur->name, "surface") == 0)
	    {
	      parse_background (cur);
	    }
	  else if (strcmp ((char*)cur->name, "music") == 0)
	    {
	      parse_music (cur);
	    }
	  else
	    {
	      printf("PingusWorldMapGraph: Unhandled: %s\n", (char*)cur->name);
	    }
	  cur = cur->next;
	}      
    }
  
  xmlFreeDoc(doc);
}

void
PingusWorldMapGraph::parse_node_list (xmlNodePtr cur)
{
  cur = cur->children;
  while (cur != NULL)
    {
      if (xmlIsBlankNode(cur)) 
	{
	  cur = cur->next;
	  continue;
	}

      if (strcmp((char*)cur->name, "empty") == 0)
	{
	  PingusWorldMapNodeData* data = PingusWorldMapEmptyNodeData::create (doc, cur);
	  nodes.push_back (boost::shared_ptr<class PingusWorldMapNode>
			   (data->create ()));
	  delete data;
	}
      else if (strcmp((char*)cur->name, "level") == 0)
	{
	  PingusWorldMapNodeData* data = PingusWorldMapLevelNodeData::create (doc, cur);
	  nodes.push_back (boost::shared_ptr<class PingusWorldMapNode>
			   (data->create ()));
	  delete data;
	}
      else if (strcmp((char*)cur->name, "tube") == 0)
	{
	  PingusWorldMapNodeData* data = PingusWorldMapTubeNodeData::create (doc, cur);
	  nodes.push_back (boost::shared_ptr<class PingusWorldMapNode>
			   (data->create ()));
	  delete data;
	}
      else
	{
	  printf("PingusWorldMapGraph:parse_node_list: Unhandled: %s\n", (char*)cur->name);	  
	}
      cur = cur->next;
    } 
}

void
PingusWorldMapGraph::parse_background (xmlNodePtr cur)
{
  bg_desc = XMLhelper::parse_surface(doc, cur);
}

void
PingusWorldMapGraph::parse_music (xmlNodePtr cur)
{
  char* file = (char*)xmlGetProp(cur, (xmlChar*)"file");

  if (file)
    music = file;
  else
    {
      std::cout << "PingusWorldMapGraph: No music file given" << std::endl;
    }
}

ResDescriptor 
PingusWorldMapGraph::get_background ()
{
  return bg_desc;
}

std::string 
PingusWorldMapGraph::get_music ()
{
  return music;
}

/*Graph<PingusWorldMapNode>* 
  PingusWorldMapGraph::get_graph ()
  {
  return graph;
  }*/

void
PingusWorldMapGraph::draw (const CL_Vector& offset)
{
  //float x_scale = CL_Display::get_width () / 800.0;
  //float y_scale = CL_Display::get_height () / 600.0;

  for (iterator i = nodes.begin();
       i != nodes.end();
       ++i)
    {
      for (iterator j = nodes.begin();
	   j != nodes.end();
	   ++j)
	{
	  CL_Vector i_pos = (*i)->get_pos ();
	  CL_Vector j_pos = (*j)->get_pos ();

	  for (std::list<int>::iterator k = (*i)->get_links ().begin();
	       k != (*i)->get_links ().end();
	       ++k)
	    if ((*j)->get_id () == *k)
	      CL_Display::draw_line ((int)(j_pos.x + offset.x), (int)(j_pos.y + offset.y),
				     (int)(i_pos.x + offset.x), (int)(i_pos.y + offset.y),
				     1.0, 1.0, 1.0, 1.0);
	}
    }
}

/* Fade out, fixme, doesn't work at the moment 
   CL_SurfaceProvider* provider = new TargetProvider (target);
   CL_Surface* sur = CL_Surface::create (provider);

   for (int y = 0; y < CL_Display::get_height(); 
   y += CL_Display::get_height() / 40)
   {
   CL_System::keep_alive ();
   CL_Display::clear_display ();
   sur->put_screen (0, y);
   Display::flip_display ();
   }
		      
   delete sur;
   delete provider;
*/

/* EOF */

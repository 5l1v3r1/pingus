//  $Id: ice_block.cxx,v 1.11 2002/09/10 14:33:07 grumbel Exp $
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
#include "../graphic_context.hxx"
#include "../col_map.hxx"
#include "../world.hxx"
#include "../pingu_holder.hxx"
#include "../pingus_resource.hxx"
#include "../xml_helper.hxx"
#include "../pingu_map.hxx"
#include "../game_time.hxx"
#include "ice_block.hxx"
#include "../pingu.hxx"
#include "../game_time.hxx"

IceBlockData::IceBlockData () : width(1)
{
}

void
IceBlockData::write_xml(std::ostream& xml)
{
  xml << "  <worldobj type=\"iceblock\">";
  XMLhelper::write_vector_xml (xml, pos);
  xml << "    <width>" << width << "</width>\n"
      << "  </worldobj>\n" << std::endl;
}

IceBlockData::IceBlockData (xmlDocPtr doc, xmlNodePtr cur)
{
  cur = cur->children;
  
  while (cur != NULL)
    {
      if (xmlIsBlankNode(cur)) 
	{
	  cur = cur->next;
	  continue;
	}
      else if (strcmp((char*)cur->name, "position") == 0)
	{
	  pos = XMLhelper::parse_vector (doc, cur);
	}
      else if (strcmp((char*)cur->name, "width") == 0)
	{
	  width = XMLhelper::parse_int (doc, cur);
	}
      else
	std::cout << "IceBlockData::creata (): Unhandled " << cur->name << std::endl;
      cur = cur->next;
    }
}

WorldObj* 
IceBlockData::create_WorldObj ()
{
  return new IceBlock (*this);
}

EditorObjLst
IceBlockData::create_EditorObj ()
{
  EditorObjLst lst; 
  lst.push_back(new EditorIceBlockObj (*this));
  return lst;
}

IceBlock::IceBlock (const IceBlockData& data)
{
  pos   = data.pos;
  width = data.width;
  block_sur = PingusResource::load_surface ("iceblock", "worldobjs");
  thickness = 1.0;
  is_finished = false;
  last_contact = 0;
}

void
IceBlock::draw_colmap()
{
  CL_Surface surf (PingusResource::load_surface("iceblock_cmap", "worldobjs"));

  world->get_colmap()->put(surf, (int)pos.x, (int)pos.y, GroundpieceData::GP_GROUND);
}

///
void 
IceBlock::draw (GraphicContext& gc)
{
  if (is_finished)
    return;

  gc.draw (block_sur, pos, (int)((1.0 - thickness) * (block_sur.get_num_frames () - 1)));
}

///
void 
IceBlock::update(float /*delta*/)
{
  if (is_finished)
    return;

  PinguHolder* holder = world->get_pingu_p();

  for (PinguIter pingu = holder->begin (); pingu != holder->end (); pingu++)
    {
      if ((*pingu)->get_x() > pos.x && (*pingu)->get_x() < pos.x + block_sur.get_width()
	  && (*pingu)->get_y() > pos.y - 4 && (*pingu)->get_y() < pos.y + block_sur.get_height())
	{
	  last_contact = world->get_game_time()->get_ticks ();
	}
    }

  if (last_contact && last_contact + 1000 > world->get_game_time ()->get_ticks ())
    {
      //std::cout << "IceBlock: Catched Pingu: " << thickness  << std::endl;
      thickness -= 0.01f;

      if (thickness < 0.0)
	{
	  is_finished = true;
	  thickness = 0.0;
	  CL_Surface surf(PingusResource::load_surface("iceblock_cmap", "worldobjs"));
	  world->get_colmap()->remove(surf, (int)pos.x, (int)pos.y);
	  world->get_gfx_map()->remove(surf, (int)pos.x, (int)pos.y);
	  return;
	}
    }
}

EditorIceBlockObj::EditorIceBlockObj (const IceBlockData& data)
  : SpriteEditorObj ("iceblock", "worldobjs", &pos)
{
  pos      = data.pos;
  IceBlockData::width = data.width;
}

/** Create the object with resonable defaults */
EditorObjLst
EditorIceBlockObj::create (const CL_Vector& pos)
{
  IceBlockData data;
  
  data.pos = pos;

  return data.create_EditorObj ();
}

std::string 
EditorIceBlockObj::status_line()
{
  char str[256];
  snprintf (str, 256, "IceBlock - %f %f %f", pos.x, pos.y, pos.z);
  return str;
}

EditorObj*
EditorIceBlockObj::duplicate()
{
  std::cout << "EditorIceBlockObj::duplicate(): Not implemented" << std::endl;
  return 0;
}

/* EOF */

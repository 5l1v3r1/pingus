//  $Id: worldobj_group_data.cxx,v 1.13 2003/10/18 23:17:28 grumbel Exp $
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
#include "../editor/editorobj_group.hxx"
#include "../xml_helper.hxx"
#include "../worldobj_data_factory.hxx"
#include "../editor/editorobj_mgr.hxx"
#include "worldobj_group_data.hxx"

namespace Pingus {
namespace WorldObjsData {

WorldObjGroupData::WorldObjGroupData ()
{
}

WorldObjGroupData::WorldObjGroupData (xmlDocPtr doc, xmlNodePtr cur)
{
  cur = cur->children;

  //std::cout << "WorldObjGroupData::WorldObjGroupData (xmlDocPtr doc, xmlNodePtr cur)" << std::endl;

  cur = XMLhelper::skip_blank (cur->next);

  while (cur)
    {
      //std::cout << "WorldObjGroupData: " << cur->name << std::endl;
      objs.push_back (WorldObjDataFactory::instance ()->create (doc, cur));
      cur = cur->next;
      cur = XMLhelper::skip_blank (cur->next);
    }

  //std::cout << "WorldObjGroupData: size = " << objs.size () << std::endl;
}

WorldObjGroupData::WorldObjGroupData (const WorldObjGroupData& data)
  : WorldObjData(data),
    objs (data.objs)
{
  // FIXME: no deep copy
  std::cout << "WorldObjGroupData::WorldObjGroupData (const WorldObjGroupData&): fixme no deep copy" << std::endl;
}

WorldObjGroupData::~WorldObjGroupData ()
{
  std::cout << "WorldObjGroupData::~WorldObjGroupData ()" << std::endl;
  for (ObjsIter i = objs.begin (); i != objs.end (); ++i)
    delete *i;
}

void
WorldObjGroupData::add (WorldObjData* data)
{
  objs.push_back (data);
}

void
WorldObjGroupData::write_xml (std::ostream& xml)
{
  xml << "<group>\n";
  for (ObjsIter i = objs.begin (); i != objs.end (); ++i)
    (*i)->write_xml (xml);
  xml << "</group>\n\n";
}

void
WorldObjGroupData::insert_WorldObjs (World* world)
{
  // Flatten all objects of the group and insert them normal into the
  // world
  for (ObjsIter i = objs.begin (); i != objs.end (); ++i)
    (*i)->insert_WorldObjs(world);
}

void
WorldObjGroupData::insert_EditorObjs (EditorNS::EditorObjMgr* obj_mgr)
{
  EditorObjGroup* group = new EditorObjGroup();

  for (ObjsIter i = objs.begin (); i != objs.end (); ++i)
    {
      (*i)->insert_EditorObjs(group);
    }

  obj_mgr->add(group);
}

} // namespace WorldObjsData
} // namespace Pingus

/* EOF */

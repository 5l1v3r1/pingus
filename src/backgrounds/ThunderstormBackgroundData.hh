//  $Id: ThunderstormBackgroundData.hh,v 1.6 2001/08/13 21:35:37 grumbel Exp $
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

#ifndef THUNDERSTORMBACKGROUNDDATA_HH
#define THUNDERSTORMBACKGROUNDDATA_HH

#include "../WorldObjData.hh"

class ThunderstormBackgroundData : public WorldObjData
{
public:
  CL_Vector pos;

  ThunderstormBackgroundData() {}
  virtual ~ThunderstormBackgroundData() {}

  /** Writte the content of this object formated as xml to the given
      stream */
  virtual void write_xml(std::ofstream* xml);
  
  static boost::shared_ptr<WorldObjData> create(xmlDocPtr doc, xmlNodePtr cur);

  boost::shared_ptr<WorldObj> create_WorldObj();
  EditorObjLst create_EditorObj();
};

#endif

/* EOF */

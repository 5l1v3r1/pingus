//  $Id: worldobj_group.hxx,v 1.1 2002/09/15 20:33:45 grumbel Exp $
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_WORLDOBJ_GROUP_HXX
#define HEADER_WORLDOBJ_GROUP_HXX

#include "../worldobj.hxx"
#include "../worldobjsdata/worldobj_group_data.hxx"

namespace WorldObj {

/** */
class WorldObjGroup : public WorldObj
{
private:
  std::vector<WorldObj*> objs;
  WorldObjGroupData* const data;
public:
  WorldObjGroup (WorldObjGroupData* data_);
  
  void update (float delta);
  void draw (GraphicContext& gc);

private:
  WorldObjGroup (const WorldObjGroup&);
  WorldObjGroup operator= (const WorldObjGroup&);
};

} // namespace WorldObj

#endif

/* EOF */

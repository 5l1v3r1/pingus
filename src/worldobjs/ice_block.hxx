//  $Id: ice_block.hxx,v 1.10 2002/09/15 11:02:24 grumbel Exp $
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

#ifndef HEADER_PINGUS_WORLDOBJS_ICE_BLOCK_HXX
#define HEADER_PINGUS_WORLDOBJS_ICE_BLOCK_HXX

#include "../worldobj.hxx"

namespace WorldObjsData {
class IceBlockData;
}

namespace WorldObjs {

class IceBlock : public WorldObj
{
private:
  WorldObjsData::IceBlockData* const data;

  float thickness;
  bool  is_finished;
  int   last_contact;
  CL_Surface block_sur;
  
public:
  IceBlock (WorldObjsData::IceBlockData* data_);
 ~IceBlock ();

  float get_z_pos () const { return 100; }
  void draw_colmap ();
  void draw (GraphicContext& gc);
  void update (float delta);
  
private:
  IceBlock (const IceBlock&);
  IceBlock operator= (const IceBlock&);
};

} // namespace WorldObjs

#endif

/* EOF */

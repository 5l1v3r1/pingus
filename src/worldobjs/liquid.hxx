//  $Id: liquid.hxx,v 1.1 2002/09/25 17:21:39 torangan Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 1999 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_WORLDOBJS_LIQUID_HXX
#define HEADER_PINGUS_WORLDOBJS_LIQUID_HXX

#include <ClanLib/Display/Display/surface.h>
#include "../anim_counter.hxx"
#include "../worldobj.hxx"

namespace WorldObjsData {
class LiquidData;
}

namespace WorldObjs {

class Liquid : public WorldObj
{
private:
  WorldObjsData::LiquidData* const data;
  CL_Surface sur;
  AnimCounter counter;
  
public:
  CL_Surface colmap_sur;

  Liquid (WorldObjsData::LiquidData* data_);
 ~Liquid ();

  float get_z_pos () const;
  void  on_startup();
  void  draw      (GraphicContext& gc);
  
private:
  Liquid (const Liquid&);
  Liquid operator= (const Liquid&);
};

} // namespace WorldObjs

#endif

/* EOF */


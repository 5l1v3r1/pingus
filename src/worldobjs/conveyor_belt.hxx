//  $Id: conveyor_belt.hxx,v 1.20 2003/10/20 13:11:09 grumbel Exp $
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

#ifndef HEADER_PINGUS_WORLDOBJS_CONVEYOR_BELT_HXX
#define HEADER_PINGUS_WORLDOBJS_CONVEYOR_BELT_HXX

#include <ClanLib/Display/sprite.h>
#include "../worldobj.hxx"
#include "../worldobj_data.hxx"

namespace Pingus {

namespace WorldObjsData {
class ConveyorBeltData;
}

namespace WorldObjs {

class ConveyorBelt : public  WorldObj
{
private:
  WorldObjsData::ConveyorBeltData* const data;

  CL_Sprite left_sur;
  CL_Sprite right_sur;
  CL_Sprite middle_sur;

public:
  ConveyorBelt (const WorldObjsData::ConveyorBeltData& data_);

  void draw (SceneContext& gc);
  void on_startup ();
  void update ();
  float get_z_pos () const;

private:
  ConveyorBelt (const ConveyorBelt&);
  ConveyorBelt& operator= (const ConveyorBelt&);
};

} // namespace WorldObjs
} // namespace Pingus

#endif

/* EOF */

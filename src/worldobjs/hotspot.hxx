//  $Id: hotspot.hxx,v 1.7 2003/10/18 23:17:28 grumbel Exp $
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

#ifndef HEADER_PINGUS_WORLDOBJS_HOTSPOT_HXX
#define HEADER_PINGUS_WORLDOBJS_HOTSPOT_HXX

#include <ClanLib/Display/sprite.h>
#include "../worldobj.hxx"

namespace Pingus {

namespace WorldObjsData {
class HotspotData;
}

namespace WorldObjs {

class Hotspot : public WorldObj
{
private:
  CL_Sprite     sprite;
  float         para;
  Vector        pos;

public:
  Hotspot(const FileReader& reader);
  ~Hotspot();

  void  draw(SceneContext& gc);
  void  update();
  float get_z_pos() const;

private:
  Hotspot (const Hotspot&);
  Hotspot& operator= (const Hotspot&);
};

} // namespace WorldObjs
} // namespace Pingus

#endif

/* EOF */


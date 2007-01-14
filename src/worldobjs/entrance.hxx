//  $Id: entrance.hxx,v 1.7 2003/10/20 13:11:09 grumbel Exp $
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

#ifndef HEADER_PINGUS_ENTRANCE_HXX
#define HEADER_PINGUS_ENTRANCE_HXX

#include <ClanLib/Display/sprite.h>
#include "../vector.hxx"
#include "../res_descriptor.hxx"
#include "../worldobj.hxx"


namespace WorldObjsData {
class EntranceData;
}

class Pingu;

namespace WorldObjs {

/** A abstract representation of an entrance, the implementation
    currently sucks and needs to be rewritten */
class Entrance : public WorldObj
{
protected:
  enum EntranceDirection { LEFT, RIGHT, MISC };
  EntranceDirection direction;
  Vector            pos;
  int               release_rate;
  int               owner_id;

  /// The type of the entrance type (woodthing, generic, etc.)
  std::string type;

  CL_Sprite smallmap_symbol;
  CL_Sprite surface;
  int        last_release;

public:
  Entrance(const FileReader& reader);
  ~Entrance();

  float get_z_pos () const;

  virtual bool   pingu_ready ();
  virtual void   create_pingu ();

  virtual void   update ();

  virtual void   draw (SceneContext& gc);

  void  draw_smallmap(SmallMap* smallmap);

private:
  Entrance (const Entrance&);
  Entrance& operator= (const Entrance&);
};

} // namespace WorldObjs

#endif

/* EOF */

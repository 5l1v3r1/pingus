//  $Id: smasher.hxx,v 1.1 2002/09/04 14:55:13 torangan Exp $
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

#ifndef HEADER_PINGUS_WORLDOBJS_SMASHER_HXX
#define HEADER_PINGUS_WORLDOBJS_SMASHER_HXX

#include "../worldobj.hxx"

namespace WorldObjsData {
  class SmasherData;
}

class Pingu;


namespace WorldObjs {

  class Smasher : public WorldObj
  {
  private:
    bool smashing;
    bool downwards;
    int  count;
    WorldObjsData::SmasherData* const data;

  public:
    Smasher (WorldObjsData::SmasherData* data_);
   ~Smasher ();

    float get_z_pos () const;
    
    void draw_offset (int x, int y, float s);
    void draw_colmap ();
    void update (float delta);

  protected:
    void catch_pingu (Pingu* pingu);

  private:
    Smasher (const Smasher&);
    Smasher operator= (const Smasher&);
  };

}

#endif

/* EOF */

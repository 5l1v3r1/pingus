//  $Id: ThunderstormBackground.hh,v 1.10 2001/08/13 21:35:37 grumbel Exp $
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

#ifndef THUNDERSTORMBACKGROUND_HH
#define THUNDERSTORMBACKGROUND_HH

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <vector>
#include "../boost/smart_ptr.hpp"
#include "SurfaceBackground.hh"
#include "ThunderstormBackgroundData.hh"

class ThunderstormBackground : public WorldObj,
			       public ThunderstormBackgroundData
{
private:
  //SurfaceBackground* background;
  CL_Surface clouds_sur;
  std::vector<CL_Surface> flash_sur;
  int x_pos;
public:
  ///
  ThunderstormBackground();
  ///
  virtual ~ThunderstormBackground();
  ///
  //static boost::shared_ptr<ThunderstormBackground> create (boost::shared_ptr<BackgroundData>);

  float get_z_pos() const { return pos.z; }
  
  void update(float delta);
  void draw_offset(int x_of, int y_of, float s = 1.0);
};

#endif

/* EOF */

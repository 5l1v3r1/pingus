//  $Id: Exit.hh,v 1.12 2000/12/30 23:54:05 grumbel Exp $
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

#ifndef EXIT_HH
#define EXIT_HH

#include <ClanLib/core.h>

#include "WorldObj.hh"
#include "ExitData.hh"
#include "Pingu.hh"
#include "AnimCounter.hh"
#include "ActionHolder.hh"

///
class Exit : public ExitData,
	     public WorldObj
{
private:
  ///
  CL_Surface surface;

  AnimCounter counter;
public:
  ///
  Exit(ExitData data);
  ///
  virtual ~Exit();
  ///
  void draw_colmap();
  ///
  void draw_offset(int x, int y, float s = 1.0);
  ///
  bool catch_pingu(boost::shared_ptr<Pingu> pingu);
  ///
  virtual int  get_z_pos() const { return pos.z_pos; }
};

#endif

/* EOF */

//  $Id: Entrance.hh,v 1.5 2000/06/19 20:10:38 grumbel Exp $
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

#ifndef ENTRANCE_HH
#define ENTRANCE_HH

#include <string>
#include <ClanLib/core.h>

#include "Pingu.hh"
#include "WorldObj.hh"
#include "particles/ParticleHolder.hh"
#include "ActionHolder.hh"
#include "entrance_data.hh"

/** A abstract representation of an entrance, the implementation
    currently sucks and needs to be rewritten */
class Entrance : public WorldObj
{
protected:
  ///
  CL_Surface* surface;
  ///
  int last_release;
  ///
  int release_rate;
  ///
  entrance_data::Direction direction;
  
  ///
  int x_pos;
  ///
  int y_pos;

  ///
  static ParticleHolder* particle;
  ///
  static ActionHolder* action_holder;
public:
  ///
  Entrance();
  ///
  Entrance(entrance_data data);

  ///
  virtual bool   pingu_ready(void);
  ///
  virtual Pingu* get_pingu(void);
  ///
  virtual void   let_move(void);
  ///
  virtual void   draw_offset(int x, int y, float s = 1.0);

  ///
  static void set_action_holder(ActionHolder* a);
  ///
  static void SetParticleHolder(ParticleHolder* p);
}///
;

#endif

/* EOF */

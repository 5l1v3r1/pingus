//  $Id: climber.hh,v 1.3 2000/05/24 18:48:35 grumbel Exp $
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

#ifndef CLIMBER_HH
#define CLIMBER_HH

#include "../PinguAction.hh"

class Climber : public PinguAction
{
private:
  static CL_Surface* static_surface;
public:
  Climber();

  void   init(void);
  void   let_move(void);
  int    x_offset(void);
  int    y_offset(void);
  PinguAction* allocate(void);
  ActionType get_type(void) { return (ActionType)WALL; }
};

#endif

/* EOF */

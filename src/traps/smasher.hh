//  $Id: smasher.hh,v 1.3 2000/04/10 21:24:44 grumbel Exp $
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

#ifndef SMASHER_HH
#define SMASHER_HH

#include "../Trap.hh"
#include "../trap_data.hh"

class Smasher : public Trap
{
private:
  bool smashing;
  bool downwards;
  int  count;
public:
  Smasher(trap_data data);
  virtual ~Smasher();
  void draw_offset(int x, int y, float s);
  void draw_colmap(ColMap*);
  void let_move();
  bool catch_pingu(Pingu* pingu);
};

#endif

/* EOF */

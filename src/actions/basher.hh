//  $Id: basher.hh,v 1.11 2001/04/08 14:10:34 grumbel Exp $
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

#ifndef BASHER_HH
#define BASHER_HH

#include "../PinguAction.hh"
#include "../GameCounter.hh"

///
class Basher : public PinguAction
{
private:
  ///
  static bool static_surf_loaded;
  ///
  static CL_Surface static_surface;
  ///
  static CL_Surface bash_radius;
  ///
  int basher_c;
  ///
  GameCounter counter;
  ///
  bool first_bash;
public:
  ///
  Basher();
  ///
  void   init(void);
  ///
  void draw_offset(int x, int y, float s);
  ///
  void   update(float delta);
  ///
  bool   have_something_to_dig();
  ///
  void   walk_forward();
  ///
  void   bash();
}///
;

#endif

/* EOF */

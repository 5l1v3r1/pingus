//  $Id: Drown.hh,v 1.9 2001/08/05 23:50:14 grumbel Exp $
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

#ifndef DROWN_HH
#define DROWN_HH

#include "../PinguAction.hh"

class Drown : public PinguAction
{
private:
  Sprite sprite;
public:
  void init();
  std::string get_name() const { return "Drown"; }
  PinguEnvironment get_environment() const { return ENV_ALWAYS; }
  void update(float delta);
  void draw_offset(int x, int y, float s);
  bool catchable () { return false; }
};

REGISTER_PINGUACTION(DrownFactory, Drown, "drown");

#endif

/* EOF */

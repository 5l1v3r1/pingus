//  $Id: floater.hxx,v 1.1 2002/06/12 19:01:42 grumbel Exp $
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

#ifndef FLOATER_HH
#define FLOATER_HH

#include "../sprite.hxx"
#include "../pingu_action.hxx"

///
class Floater : public PinguAction
{
private:
  int falling_depth;
  int step;
  Sprite sprite;
public:
  ///
  Floater();

  std::string get_name() const { return "Floater"; }
  PinguEnvironment get_environment() const { return PinguEnvironment(ENV_LAND|ENV_AIR); }
  ActionType get_type(void) { return FALL; };
  void init(void);
  void update(float delta);
  void draw_offset (int x, int y, float s);
  char get_persistent_char () { return 'f'; }
};

#endif

/* EOF */

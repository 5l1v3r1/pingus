//  $Id: climber.hxx,v 1.2 2002/06/24 22:52:57 grumbel Exp $
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

#ifndef HEADER_PINGUS_ACTIONS_CLIMBER_HXX
#define HEADER_PINGUS_ACTIONS_CLIMBER_HXX

#include "../sprite.hxx"
#include "../pingu_action.hxx"

///
class Climber : public PinguAction
{
private:
  Sprite sprite;
  int sprite_width, sprite_height;
public:
  Climber();
  void   init();
  std::string get_name () const { return "Climber"; }
  PinguEnvironment get_environment() const { return PinguEnvironment(ENV_LAND|ENV_AIR); }
  void draw_offset(int x, int y, float s=1.0);
  void update(float delta);
  ActionType get_type(void) { return (ActionType)WALL; }
  char get_persistent_char () { return 'c'; }
};

#endif

/* EOF */

//  $Id: Jumper.hh,v 1.13 2001/08/16 17:46:51 grumbel Exp $
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

#ifndef JUMPER_HH
#define JUMPER_HH

#include "../Sprite.hh"
#include "../PinguAction.hh"

///
class Jumper : public PinguAction
{
private:
  Sprite sprite;
public:
  Jumper();

  void  init(void);
  PinguEnvironment get_environment () const { return (PinguEnvironment)ENV_LAND; }
  std::string get_name() const { return "Jumper"; }
  void  update(float delta);
  void  draw_offset(int x, int y, float s);
};

#endif

/* EOF */

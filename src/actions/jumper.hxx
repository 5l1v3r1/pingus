//  $Id: jumper.hxx,v 1.9 2002/09/27 11:26:44 torangan Exp $
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

#ifndef HEADER_PINGUS_ACTIONS_JUMPER_HXX
#define HEADER_PINGUS_ACTIONS_JUMPER_HXX

#include "../sprite.hxx"
#include "../pingu_action.hxx"

namespace Actions {

class Jumper : public PinguAction
{
private:
  Sprite sprite;
public:
  Jumper();

  void  init(void);
  std::string get_name() const { return "Jumper"; }
  ActionName get_type() const { return Actions::Jumper; }

  void  draw (GraphicContext& gc);
  void  update(float delta);
  
private:
  Jumper (const Jumper&);
  Jumper& operator= (const Jumper&);
};

} // namespace Actions

#endif

/* EOF */

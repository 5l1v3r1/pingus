//  $Id: blocker.hxx,v 1.6 2002/08/23 15:49:53 torangan Exp $
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

#ifndef HEADER_PINGUS_ACTIONS_BLOCKER_HXX
#define HEADER_PINGUS_ACTIONS_BLOCKER_HXX

#include "../sprite.hxx"
#include "../pingu_action.hxx"

///
class Blocker : public PinguAction
{
private:
  Sprite sprite;
public:
  ///
  Blocker();
  ///
  int   y_offset();
  ///
  void  init();
  std::string get_name () const { return "Blocker"; }
  Pingus::Actions::ActionName get_type() const { return Pingus::Actions::Blocker; }
 
  void  update(float delta);
  void  draw_offset(int, int, float s);
  bool  standing_on_ground();
  ///
  bool  need_catch();
  ///
  void  catch_pingu(Pingu* pingu);
  
private:
  Blocker (const Blocker&);
  Blocker operator= (const Blocker&);
};

#endif

/* EOF */

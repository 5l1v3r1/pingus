//  $Id: rocket_launcher.hxx,v 1.9 2002/09/27 11:26:44 torangan Exp $
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

#ifndef HEADER_PINGUS_ACTIONS_ROCKET_LAUNCHER_HXX
#define HEADER_PINGUS_ACTIONS_ROCKET_LAUNCHER_HXX

#include "../sprite.hxx"
#include "../pingu_action.hxx"

namespace Actions {

class RocketLauncher : public PinguAction
{
private:
  Sprite sprite;
  bool launched;
public:
  RocketLauncher () {}
  ~RocketLauncher () {}

  void  init ();
  
  std::string get_name () const { return "RocketLauncher"; }
  ActionName get_type () const { return Actions::Rocketlauncher; }
  
  void draw (GraphicContext& gc);
  void update (float delta);
  
private:
  RocketLauncher (const RocketLauncher&);
  RocketLauncher& operator= (const RocketLauncher&);
};

} // namespace Actions

#endif

/* EOF */

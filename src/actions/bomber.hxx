//  $Id: bomber.hxx,v 1.21 2003/10/18 23:17:27 grumbel Exp $
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

#ifndef HEADER_PINGUS_ACTIONS_BOMBER_HXX
#define HEADER_PINGUS_ACTIONS_BOMBER_HXX

#include "../state_sprite.hxx"
#include "../pingu_action.hxx"

namespace Pingus {
namespace Actions {

/** An action with lets the Pingu explode. After the explosion the the
    Pingu leaves a hole inside the ground. */
class Bomber : public PinguAction
{
private:
  bool particle_thrown;
  bool sound_played;
  bool gfx_exploded;
  bool colmap_exploded;

  static bool static_surface_loaded;
  static CL_PixelBuffer bomber_radius;
  static CL_PixelBuffer bomber_radius_gfx;

  StateSprite sprite;
  CL_Sprite   explo_surf;

public:
  Bomber (Pingu* p);

  ActionName get_type() const { return Actions::Bomber; }
  ActionType get_activation_mode() const { return COUNTDOWN_TRIGGERED; }

  void draw (DrawingContext& gc);
  void update();

  int  activation_time() { return 150; }
  void on_successfull_apply ();

private:
  Bomber (const Bomber&);
  Bomber& operator= (const Bomber&);
};

} // namespace Actions
} // namespace Pingus

#endif

/* EOF */
